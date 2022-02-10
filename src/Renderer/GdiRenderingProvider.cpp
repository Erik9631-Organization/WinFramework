//
// Created by Erik on 22/01/24.
//
#include <windows.h>
#include <gdiplus.h>
#include "GdiRenderingProvider.h"
#include "CoreWindow.h"
#include "Window.h"
#include "RenderEventInfo.h"
#include "EventResizeInfo.h"
#include "GdiRenderer.h"
#include <algorithm>
#include <execution>
#include <future>
#include <chrono>
using namespace std::chrono;

using namespace Gdiplus;
void GdiRenderingProvider::Render()
{
    //Change the rendering bit
    CoreWindow::ConsoleWrite("Render requested");
    performRender = true;
    performRenderSignal.notify_one();
}

void GdiRenderingProvider::CleanBackBuffer()
{
    ReleaseDC(windowHandle, secondaryDc);
    DeleteDC(secondaryDc);
}

void GdiRenderingProvider::AssignGraphicsToNodes(MultiTree<UiElement&>& node, Gdiplus::Region& clippingRegion)
{
    Graphics graphics(secondaryDc);
    GdiRenderer renderer{graphics};
    graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

    if(!node.IsRoot())
    {
        Vector2 viewPortAbsPos = node.GetValue().GetViewportAbsolutePosition();
        Vector2 viewPortAbsSize = node.GetValue().GetViewportAbsoluteSize();
        RectF viewport = RectF(viewPortAbsPos.GetX(), viewPortAbsPos.GetY(), viewPortAbsSize.GetX(), viewPortAbsSize.GetY());
        graphics.SetClip(viewport);
        clippingRegion.Intersect(viewport);
        graphics.IntersectClip(&clippingRegion);

        //translate
        Matrix transformMatrix;
        transformMatrix.Translate(node.GetValue().GetAbsoluteX(), node.GetValue().GetAbsoluteY());
        graphics.SetTransform(&transformMatrix);
    }
    RenderEventInfo renderEvent{RenderEventInfo{&renderer}};

    node.GetValue().OnRender(renderEvent);

    for (int i = 0; i < node.GetNodeCount(); i++)
    {
        Region* newRegion = clippingRegion.Clone();
        AssignGraphicsToNodes(node.Get(i), *newRegion);
        delete newRegion;
    }
}

void GdiRenderingProvider::AssignGraphicsToNodes()
{
    Window& wrapperFrame = coreWindowframe->GetWrapperFrame();
    Gdiplus::Rect rootViewport = Rect(0, 0, wrapperFrame.GetWidth() + 1, wrapperFrame.GetHeight() + 1);
    Gdiplus::Region clippingRegion = Gdiplus::Region(rootViewport);
    AssignGraphicsToNodes(wrapperFrame.GetUiElementNode(), clippingRegion);
}

HDC GdiRenderingProvider::GetSecondaryDC()
{
    secondaryDc = CreateCompatibleDC(windowHdc);
    SelectObject(secondaryDc, secondaryBitmap);
    return secondaryDc;
}

void GdiRenderingProvider::OnResize(EventResizeInfo e)
{
    Size size = {(int)e.GetSize().GetX(), (int)e.GetSize().GetY()};
    secondaryBitmap = CreateCompatibleBitmap(GetWindowDC(windowHandle), size.Width, size.Height);
}

void GdiRenderingProvider::OnInit(CoreWindow &coreWindowFrame)
{
    this->coreWindowframe = &coreWindowFrame;
    windowHandle = coreWindowframe->GetWindowHandle();
    windowHdc = GetDC(windowHandle);
    coreWindowframe->AddOnResizePreProcessSubsriber(*this);
    secondaryBitmap = CreateCompatibleBitmap(windowHdc, coreWindowframe->GetWrapperFrame().GetWidth(),
                                             coreWindowframe->GetWrapperFrame().GetHeight());
    performRender = !coreWindowframe->IsEventBased();
    fpsTimer.Start();

    if(renderingThread == nullptr)
        renderingThread = std::make_unique<std::thread>([=]{ InternalRender();});
}

void GdiRenderingProvider::OnDestroy(CoreWindow &coreWindow)
{
    CleanBackBuffer();
    startRenderingLoop = false;
    //CoreWindow::ConsoleWrite("Render thread ending!");
    fpsTimer.Stop();
    renderingThread->join();
    //CoreWindow::ConsoleWrite("Render thread ended!");
}

void GdiRenderingProvider::OnRemove(CoreWindow &coreWindow)
{
    coreWindow.RemoveOnResizePreProcessSubsriber(*this);
}

[[noreturn]] void GdiRenderingProvider::InternalRender()
{

    while(startRenderingLoop)
    {

        long long start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        //fpsTimer.Start();
        //Render only if the rendering was requested
        mutex lockMutex;
        std::unique_lock<std::mutex>performRenderLock(lockMutex);

        CoreWindow::ConsoleWrite("Waiting for render");
        performRenderSignal.wait(performRenderLock, [=]{return performRender;});
        //OnSync
        //Sync only if updating is finished.
        coreWindowframe->WaitForUpdateToFinish();
        syncFinished = false;
        CoreWindow::ConsoleWrite("Syncing data");
        SyncData(coreWindowframe->GetWrapperFrame().GetUiElementNode());
        syncFinished = true;
        CoreWindow::ConsoleWrite("Syncing finished");
        syncFinishedSignal.notify_all();

        CoreWindow::ConsoleWrite("Rendering data");
        GetSecondaryDC();
        AssignGraphicsToNodes(); //This is where components draw on the buffer
        BitBlt(windowHdc, 0, 0, coreWindowframe->GetWrapperFrame().GetWidth(), coreWindowframe->GetWrapperFrame().GetHeight(), secondaryDc, 0, 0, MERGECOPY);
        CleanBackBuffer(); // No longer needed as it window will use CS_OWNDC
        performRender = !coreWindowframe->IsEventBased();
        //fpsTimer.Wait();
        long long end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        //CoreWindow::ConsoleWrite("FPS: " + to_string(1000/(end - start)));
    }
}

void GdiRenderingProvider::SyncData(MultiTree<UiElement &> &node)
{
    //Notify current node, then go to the next one.
    std::future<void> syncResult = std::async(std::launch::async, [&]{node.GetValue().OnSync(defaultDrawData);});
    std::for_each(std::execution::par, node.GetNodes().begin(), node.GetNodes().end(), [&](MultiTree<UiElement &>& i)
    {
        SyncData(i);
    });
    syncResult.wait();
}

void GdiRenderingProvider::WaitForSyncToFinish()
{
    if(!syncFinished)
        CoreWindow::ConsoleWrite("Waiting for sync to finish");
    else
        CoreWindow::ConsoleWrite("No sync, continuing");
    mutex lockMutex;
    std::unique_lock<std::mutex>syncFinishedLock(lockMutex);
    syncFinishedSignal.wait(syncFinishedLock, [=]{return syncFinished;});
}

int GdiRenderingProvider::GetTargetFps() const
{
    return targetFps;
}

void GdiRenderingProvider::SetTargetFps(int targetFps)
{
    this->targetFps = targetFps;
    fpsTimer.SetInterval(1000/targetFps);
    fpsTimer.SetPeriodic(false);
}

GdiRenderingProvider::GdiRenderingProvider() : fpsTimer(0)
{
    fpsTimer.SetPeriodic(false);
    int interval = 1000/targetFps;
    fpsTimer.SetInterval(interval);
    renderingThread.reset();

}
