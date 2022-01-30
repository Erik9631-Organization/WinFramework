//
// Created by Erik on 22/01/24.
//
#include <windows.h>
#include <gdiplus.h>
#include "GdiRenderingProvider.h"
#include "CoreWindowFrame.h"
#include "WindowFrame.h"
#include "RenderEventInfo.h"
#include "EventResizeInfo.h"
#include "GdiRenderer.h"

using namespace Gdiplus;
void GdiRenderingProvider::AssignRenderer()
{
    GetSecondaryDC();
    AssignGraphicsToNodes(); //This is where components draw on the buffer
    BitBlt(windowHdc, 0, 0, coreWindowframe->GetWrapperFrame().GetWidth(), coreWindowframe->GetWrapperFrame().GetHeight(), secondaryDc, 0, 0, MERGECOPY);
    CleanGraphicsBuffer();
}

void GdiRenderingProvider::CleanGraphicsBuffer()
{
    ReleaseDC(windowHandle, secondaryDc);
    ReleaseDC(windowHandle, windowHdc);
    DeleteDC(secondaryDc);
    DeleteDC(windowHdc);
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
    WindowFrame& wrapperFrame = coreWindowframe->GetWrapperFrame();
    Gdiplus::Rect rootViewport = Rect(0, 0, wrapperFrame.GetWidth() + 1, wrapperFrame.GetHeight() + 1);
    Gdiplus::Region clippingRegion = Gdiplus::Region(rootViewport);
    AssignGraphicsToNodes(wrapperFrame.GetUiElementNode(), clippingRegion);
}

HDC GdiRenderingProvider::GetSecondaryDC()
{
    windowHdc = GetDC(windowHandle);
    secondaryDc = CreateCompatibleDC(windowHdc);
    SelectObject(secondaryDc, secondaryBitmap);
    return secondaryDc;
}

void GdiRenderingProvider::OnResize(EventResizeInfo e)
{
    Size size = {(int)e.GetSize().GetX(), (int)e.GetSize().GetY()};
    secondaryBitmap = CreateCompatibleBitmap(GetWindowDC(windowHandle), size.Width, size.Height);
}

void GdiRenderingProvider::OnInit(CoreWindowFrame &coreWindowFrame)
{
    this->coreWindowframe = &coreWindowFrame;
    windowHandle = coreWindowframe->GetWindowHandle();
    coreWindowframe->SetRenderingProvider(*this);
    coreWindowframe->AddOnResizePreProcessSubsriber(*this);
    secondaryBitmap = CreateCompatibleBitmap(GetWindowDC(windowHandle), coreWindowframe->GetWrapperFrame().GetWidth(),
                                             coreWindowframe->GetWrapperFrame().GetHeight());
}
