//
// Created by Erik on 22/01/24.
//
#include "GdiRenderingProvider.h"
#include "Core/Windows/WindowsCore.h"
#include "Window.h"
#include "RenderEventInfo.h"
#include "EventResizeInfo.h"
#include "GdiRenderer.h"
#include <execution>
#include <future>
#include <chrono>
#include "GdiRenderingPool.h"
#include "ApplicationController.h"
using namespace std;
using namespace chrono;
using namespace Gdiplus;

ULONG GdiRenderingProvider::token = 0;
Gdiplus::GdiplusStartupOutput GdiRenderingProvider::output = {};

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
//    Graphics graphics(secondaryDc);
//    GdiRenderer renderer{graphics};
//    GdiRenderingPool gdiRenderingPool{&renderer};
//    graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
//
//    if(!node.IsRoot())
//    {
//        glm::vec2 viewPortAbsPos = node.GetValue()->GetViewportAbsolutePosition();
//        glm::vec2 viewPortAbsSize = node.GetValue()->GetViewportAbsoluteSize();
//        RectF viewport = RectF(viewPortAbsPos.x, viewPortAbsPos.y, viewPortAbsSize.x, viewPortAbsSize.y);
//        graphics.SetClip(viewport);
//        clippingRegion.Intersect(viewport);
//        graphics.IntersectClip(&clippingRegion);
//
//        //translate
//        Matrix transformMatrix;
//        transformMatrix.Translate(node.GetValue()->GetAbsoluteX(), node.GetValue()->GetAbsoluteY());
//        graphics.SetTransform(&transformMatrix);
//    }
//    RenderEventInfo renderEvent{&gdiRenderingPool};
//
//    node.GetValue()->OnRenderSync(renderEvent);
//
//    for (int i = 0; i < node.GetNodeCount(); i++)
//    {
//        Region* newRegion = clippingRegion.Clone();
//        AssignGraphicsToNodes(node.GetNode(i), *newRegion);
//        delete newRegion;
//    }
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

//TODO should be handled by redraw
void GdiRenderingProvider::OnResize(EventResizeInfo e)
{
//    auto size = Size((int)e.GetSize().x, (int)e.GetSize().y);
//    secondaryBitmap = CreateCompatibleBitmap(GetWindowDC(windowHandle), size.Width, size.Height);
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
    GetSecondaryDC();
//    performRender = !windowsCore->IsEventBased();
//    fpsTimer.Start();

//    if(renderingThread == nullptr)
//        renderingThread = &ApplicationController::GetApplicationController()->CreateThread([=]{ InternalRender();}, to_string((long long)this)+"renderingThread");
}

void GdiRenderingProvider::OnDestroy(Core &coreWindow)
{
    CleanBackBuffer();
    startRenderingLoop = false;
    //CoreWindow::ConsoleWrite("Render thread ending!");
    fpsTimer.Stop();
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
    GdiStartup();
    fpsTimer.SetPeriodic(false);
    int interval = 1000/targetFps;
    fpsTimer.SetInterval(interval);
    renderingThread = nullptr;
}

void GdiRenderingProvider::GdiStartup()
{
    if(token != 0)
        return;

    //Startup GDI
    GdiplusStartupInput input;
    input.GdiplusVersion = 1;
    input.SuppressBackgroundThread = FALSE;
    input.DebugEventCallback = NULL;
    GdiplusStartup(reinterpret_cast<ULONG_PTR *>(&token), &input, &output);
}

std::unique_ptr<Renderer> GdiRenderingProvider::AcquireRenderer()
{
    auto graphics = std::make_unique<Graphics>(secondaryDc);
    auto renderer = new GdiRenderer(std::move(graphics));
    return std::unique_ptr<Renderer>(renderer);
}

void GdiRenderingProvider::SwapScreenBuffer()
{
    BitBlt(windowHdc, 0, 0, windowsCore->GetWrapperFrame()->GetWidth(), windowsCore->GetWrapperFrame()->GetHeight(), secondaryDc, 0, 0, MERGECOPY);
    CleanBackBuffer(); // Cleans only the SecondaryDC, as the window has permanent DC
    GetSecondaryDC();
}
