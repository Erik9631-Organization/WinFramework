//
// Created by Erik on 22/01/24.
//
#include <windows.h>
#include <gdiplus.h>
#include "GdiRenderingProvider.h"
#include "WindowsCore.h"
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
        glm::vec2 viewPortAbsPos = node.GetValue()->GetViewportAbsolutePosition();
        glm::vec2 viewPortAbsSize = node.GetValue()->GetViewportAbsoluteSize();
        RectF viewport = RectF(viewPortAbsPos.x, viewPortAbsPos.y, viewPortAbsSize.x, viewPortAbsSize.y);
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
    auto& wrapperFrame = coreWindowframe->GetWrapperFrame();
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
    auto size = Size((int)e.GetSize().x, (int)e.GetSize().y);
    secondaryBitmap = CreateCompatibleBitmap(GetWindowDC(windowHandle), size.Width, size.Height);
}

void GdiRenderingProvider::OnInit(WindowsCore &coreWindowFrame)
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
        renderingThread = &ApplicationController::GetApplicationController()->CreateThread([=]{ InternalRender();}, to_string((long long)this)+"renderingThread");
}

void GdiRenderingProvider::OnDestroy(WindowsCore &coreWindow)
{
    CleanBackBuffer();
    startRenderingLoop = false;
    //CoreWindow::ConsoleWrite("Render thread ending!");
    fpsTimer.Stop();
    renderingThread->join();
    //CoreWindow::ConsoleWrite("Render thread ended!");
}

void GdiRenderingProvider::OnRemove(WindowsCore &coreWindow)
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
        //OnSync
        //Sync only if updating is finished.
        coreWindowframe->WaitForUpdateToFinish();
        //CoreWindow::ConsoleWrite("Syncing data");
        syncer.SyncData(coreWindowframe->GetWrapperFrame().GetUiElementNode());
        //CoreWindow::ConsoleWrite("Syncing finished");

        //CoreWindow::ConsoleWrite("Rendering data");
        GetSecondaryDC();
        AssignGraphicsToNodes(); //This is where components draw on the buffer
        BitBlt(windowHdc, 0, 0, coreWindowframe->GetWrapperFrame().GetWidth(), coreWindowframe->GetWrapperFrame().GetHeight(), secondaryDc, 0, 0, MERGECOPY);
        CleanBackBuffer(); // Cleans only the SecondaryDC, as the window has permanent DC
        performRender = !coreWindowframe->IsEventBased();
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
