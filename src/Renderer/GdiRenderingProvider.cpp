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
#include "OnSyncCompleteSubscriber.h"

using namespace Gdiplus;
void GdiRenderingProvider::AssignRenderer()
{
    Render();
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
}

void GdiRenderingProvider::OnDestroy(CoreWindow &coreWindow)
{
    CleanBackBuffer();
}

void GdiRenderingProvider::OnRemove(CoreWindow &coreWindow)
{
    coreWindow.RemoveOnResizePreProcessSubsriber(*this);
}

void GdiRenderingProvider::Render()
{
    //OnSync
    SyncData(coreWindowframe->GetWrapperFrame().GetUiElementNode());
    //Wait for sync to finish
    NotifyOnSyncComplete(*this);
    //Notify the core that onSync was finished.


    GetSecondaryDC();
    AssignGraphicsToNodes(); //This is where components draw on the buffer
    BitBlt(windowHdc, 0, 0, coreWindowframe->GetWrapperFrame().GetWidth(), coreWindowframe->GetWrapperFrame().GetHeight(), secondaryDc, 0, 0, MERGECOPY);
    CleanBackBuffer(); // No longer needed as it window will use CS_OWNDC
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

void GdiRenderingProvider::NotifyOnSyncComplete(OnSyncCompleteSubject &src)
{
    if(onSyncCompleteSubscriber != nullptr)
        onSyncCompleteSubscriber->OnSyncComplete(src);

}

void GdiRenderingProvider::AddOnSyncSubscriber(OnSyncCompleteSubscriber &subscriber)
{
    onSyncCompleteSubscriber = &subscriber;
}

void GdiRenderingProvider::RemoveOnSyncSubscriber(OnSyncCompleteSubscriber &subscriber)
{
    if(onSyncCompleteSubscriber == &subscriber)
        onSyncCompleteSubscriber = nullptr;
}
