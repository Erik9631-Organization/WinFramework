//
// Created by Erik on 22/01/24.
//
#include "GdiRenderer.h"
#include "Core/Windows/WindowsCore.h"
#include "Window.h"
#include "EventResizeInfo.h"
#include "GdiShapeRenderer.h"
#include <execution>
#include <chrono>
#include "GdiRenderingPool.h"
#include "RectangleModel.h"
#include "EllipseModel.h"
#include <iostream>

using namespace std;
using namespace chrono;
using namespace Gdiplus;

ULONG GdiRenderer::token = 0;
Gdiplus::GdiplusStartupOutput GdiRenderer::output = {};

void GdiRenderer::Render()
{
    for (auto it = modelContainer.GetZIndexMap().rbegin(); it != modelContainer.GetZIndexMap().rend(); ++it)
        it->second->Draw();
}

void GdiRenderer::DeleteSecondaryDc()
{
    DeleteDC(secondaryDc);
    GetLastError();
}

void GdiRenderer::CreateSecondaryDc()
{
    DeleteSecondaryDc();
    secondaryDc = CreateCompatibleDC(windowHdc);
    SelectObject(secondaryDc, screenBitmap);
}

GdiRenderer::GdiRenderer() : modelContainer(*this)
{
    GdiStartup();
}

void GdiRenderer::GdiStartup()
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

std::unique_ptr<ShapeRenderer> GdiRenderer::AcquireShapeRenderer()
{
    auto graphics = std::make_unique<Graphics>(secondaryDc);
    auto renderer = new GdiShapeRenderer(std::move(graphics));
    return std::unique_ptr<ShapeRenderer>(renderer);
}

void GdiRenderer::SwapScreenBuffer()
{
    BitBlt(windowHdc, 0, 0, viewPortSize.x, viewPortSize.y, secondaryDc, 0, 0, SRCCOPY);
}
RenderingModel *GdiRenderer::GetModel(size_t index)
{
    return modelContainer.GetModel(index);
}

RenderingModel * GdiRenderer::CreateModel(SubCommands createCommand)
{
    auto* model = modelContainer.CreateModel(createCommand);
    return model;
}

void GdiRenderer::SetViewportSize(const glm::ivec2 &size)
{
    viewPortSize = size;
    UpdateBitmap();
    CreateSecondaryDc();
}

void GdiRenderer::UpdateBitmap()
{
    DeleteObject(screenBitmap);
    screenBitmap = CreateCompatibleBitmap(windowHdc, viewPortSize.x, viewPortSize.y);
}

void GdiRenderer::OnCoreInit(const EventCoreLifecycleInfo &e)
{

}

void GdiRenderer::OnCoreStart(const EventCoreLifecycleInfo &e)
{
    this->windowsCore = dynamic_cast<WindowsCore*>(e.GetCore());
    viewPortSize = this->windowsCore->GetWrapperFrame()->GetSize();
    if(this->windowsCore == nullptr)
    {
        /*TODO ADD LOGGING*/
        //Exit the application with an error
    }
    windowHdc = windowsCore->GetHdc();

    screenBitmap = CreateCompatibleBitmap(windowHdc, windowsCore->GetWrapperFrame()->GetSize().x,
            windowsCore->GetWrapperFrame()->GetSize().y);
    CreateSecondaryDc();
}

void GdiRenderer::OnCoreStop(const EventCoreLifecycleInfo &e)
{
    DeleteSecondaryDc();
}

void GdiRenderer::OnCoreDestroy(const EventCoreLifecycleInfo &e)
{

}

const glm::ivec2 &GdiRenderer::GetViewportSize() const
{
    return viewPortSize;
}
