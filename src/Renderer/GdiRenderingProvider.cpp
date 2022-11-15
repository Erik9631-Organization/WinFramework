//
// Created by Erik on 22/01/24.
//
#include <windows.h>
#include <gdiplus.h>
#include "GdiRenderingProvider.h"
#include "Core/Windows/WindowsCore.h"
#include "Window.h"
#include "RenderEventInfo.h"
#include "EventResizeInfo.h"
#include "GdiRenderer.h"
#include <algorithm>
#include <execution>
#include <future>
#include <chrono>
#include "GdiRenderingPool.h"
#include "ApplicationController.h"

using namespace std::chrono;

using namespace Gdiplus;
void GdiRenderingProvider::Render()
{
    //Change the rendering bit
    //CoreWindow::ConsoleWrite("Render requested");
    performRender = true;
    performRenderSignal.notify_one();
}

void GdiRenderingProvider::CleanBackBuffer()
{
    ReleaseDC(windowHandle, secondaryDc);
    DeleteDC(secondaryDc);
}

void GdiRenderingProvider::AssignGraphicsToNodes(MultiTree<std::unique_ptr<UiElement>> &node, Gdiplus::Region& clippingRegion)
{
    Graphics graphics(secondaryDc);
    GdiRenderer renderer{graphics};
    GdiRenderingPool gdiRenderingPool{&renderer};
    graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

    if(!node.IsRoot())
    {
        Vector2 viewPortAbsPos = node.GetValue()->GetViewportAbsolutePosition();
        Vector2 viewPortAbsSize = node.GetValue()->GetViewportAbsoluteSize();
        RectF viewport = RectF(viewPortAbsPos.GetX(), viewPortAbsPos.GetY(), viewPortAbsSize.GetX(), viewPortAbsSize.GetY());
        graphics.SetClip(viewport);
        clippingRegion.Intersect(viewport);
        graphics.IntersectClip(&clippingRegion);

        //translate
        Matrix transformMatrix;
        transformMatrix.Translate(node.GetValue()->GetAbsoluteX(), node.GetValue()->GetAbsoluteY());
        graphics.SetTransform(&transformMatrix);
    }
    RenderEventInfo renderEvent{&gdiRenderingPool};

    node.GetValue()->OnRenderSync(renderEvent);

    for (int i = 0; i < node.GetNodeCount(); i++)
    {
        Region* newRegion = clippingRegion.Clone();
        AssignGraphicsToNodes(node.GetNode(i), *newRegion);
        delete newRegion;
    }
}

void GdiRenderingProvider::AssignGraphicsToNodes()
{
    Window* wrapperFrame = windowsCore->GetWrapperFrame();
    if(wrapperFrame == nullptr)
        return;
    Gdiplus::Rect rootViewport = Rect(0, 0, wrapperFrame->GetWidth() + 1, wrapperFrame->GetHeight() + 1);
    Gdiplus::Region clippingRegion = Gdiplus::Region(rootViewport);
    AssignGraphicsToNodes(wrapperFrame->GetUiElementNode(), clippingRegion);
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

void GdiRenderingProvider::OnInit(Core &coreWindowFrame)
{
    this->windowsCore = dynamic_cast<WindowsCore*>(&coreWindowFrame);
    if(this->windowsCore == nullptr)
    {
        /*TODO ADD LOGGING*/
        //Exit the application with an error
    }
    windowHandle = windowsCore->GetWindowHandle();
    windowHdc = GetDC(windowHandle);
    windowsCore->AddOnResizePreProcessSubsriber(*this);

    secondaryBitmap = CreateCompatibleBitmap(windowHdc, windowsCore->GetWrapperFrame()->GetWidth(),
                                             windowsCore->GetWrapperFrame()->GetHeight());
    performRender = !windowsCore->IsEventBased();
    fpsTimer.Start();

    if(renderingThread == nullptr)
        renderingThread = &ApplicationController::GetApplicationController()->CreateThread([=]{ InternalRender();}, to_string((long long)this)+"renderingThread");
}

void GdiRenderingProvider::OnDestroy(Core &coreWindow)
{
    CleanBackBuffer();
    startRenderingLoop = false;
    //CoreWindow::ConsoleWrite("Render thread ending!");
    fpsTimer.Stop();
    renderingThread->join();
    //CoreWindow::ConsoleWrite("Render thread ended!");
}

void GdiRenderingProvider::OnRemove(Core &coreWindow)
{
    coreWindow.RemoveOnResizePreProcessSubsriber(*this);
    CleanBackBuffer();
    startRenderingLoop = false;
    //CoreWindow::ConsoleWrite("Render thread ending!");
    fpsTimer.Stop();
    renderingThread->join();
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

        //CoreWindow::ConsoleWrite("Waiting for render");
        performRenderSignal.wait(performRenderLock, [=]{return performRender;});
        if(windowsCore == nullptr)
            continue;
        //OnSync
        //Sync only if updating is finished.
        windowsCore->WaitForUpdateToFinish();
        //CoreWindow::ConsoleWrite("Syncing data");
        syncer.SyncData(windowsCore->GetWrapperFrame()->GetUiElementNode());
        //CoreWindow::ConsoleWrite("Syncing finished");

        //CoreWindow::ConsoleWrite("Rendering data");
        GetSecondaryDC();
        AssignGraphicsToNodes(); //This is where components draw on the buffer
        BitBlt(windowHdc, 0, 0, windowsCore->GetWrapperFrame()->GetWidth(), windowsCore->GetWrapperFrame()->GetHeight(), secondaryDc, 0, 0, MERGECOPY);
        CleanBackBuffer(); // Cleans only the SecondaryDC, as the window has permanent DC
        performRender = !windowsCore->IsEventBased();
        //fpsTimer.Wait();
        long long end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        //CoreWindow::ConsoleWrite("FPS: " + to_string(1000/(end - start)));
    }
}


void GdiRenderingProvider::WaitForSyncToFinish()
{
    syncer.WaitForSync();
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
    renderingThread = nullptr;
}

void GdiRenderingProvider::OnEntryStart()
{

}

void GdiRenderingProvider::OnEntryEnd()
{

}
