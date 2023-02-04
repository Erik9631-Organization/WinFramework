//
// Created by Erik on 22/01/24.
//
#include "GdiRenderer.h"
#include "Core/Windows/WindowsCore.h"
#include "Window.h"
#include "EventResizeInfo.h"
#include "GdiRenderingApi.h"
#include <execution>
#include <chrono>
#include "GdiRenderingPool.h"
#include "RectangleModel.h"
#include <iostream>

using namespace std;
using namespace chrono;
using namespace Gdiplus;

ULONG GdiRenderer::token = 0;
Gdiplus::GdiplusStartupOutput GdiRenderer::output = {};

void GdiRenderer::Render()
{
    std::lock_guard<std::mutex> lock(setViewPortMutex);
    for (auto it = modelZIndexMap.rbegin(); it != modelZIndexMap.rend(); ++it)
        it->second->Redraw();
}

void GdiRenderer::CleanDeviceContext()
{
    DeleteDC(secondaryDc);
    GetLastError();
}

void GdiRenderer::UpdateSecondaryDC()
{
    CleanDeviceContext();
    secondaryDc = CreateCompatibleDC(windowHdc);
    SelectObject(secondaryDc, screenBitmap);
}

void GdiRenderer::OnInit(Core &coreWindowFrame)
{
    this->windowsCore = dynamic_cast<WindowsCore*>(&coreWindowFrame);
    viewPortSize = this->windowsCore->GetWrapperFrame()->GetSize();
    if(this->windowsCore == nullptr)
    {
        /*TODO ADD LOGGING*/
        //Exit the application with an error
    }
    windowHandle = windowsCore->GetWindowHandle();
    windowHdc = GetDC(windowHandle);
    windowsCore->AddOnResizePreProcessSubsriber(*this);

    screenBitmap = CreateCompatibleBitmap(windowHdc, windowsCore->GetWrapperFrame()->GetWidth(),
                                          windowsCore->GetWrapperFrame()->GetHeight());
    UpdateSecondaryDC();
}

void GdiRenderer::OnDestroy(Core &coreWindow)
{
    CleanDeviceContext();
}

GdiRenderer::GdiRenderer()
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
///TODO This function should be removed and redraw should pass the rendering api though the ScheduleRedraw function as an event
std::unique_ptr<RenderingApi> GdiRenderer::AcquireRenderingApi()
{
    auto graphics = std::make_unique<Graphics>(secondaryDc);
    auto renderer = new GdiRenderingApi(std::move(graphics));
    return std::unique_ptr<RenderingApi>(renderer);
}

void GdiRenderer::SwapScreenBuffer()
{
    std::lock_guard<std::mutex> viewPortLock{setViewPortMutex};
    BitBlt(windowHdc, 0, 0, viewPortSize.x, viewPortSize.y, secondaryDc, 0, 0, MERGECOPY);
}

RenderingModel * GdiRenderer::AddModel(std::unique_ptr<RenderingModel> renderingModel)
{
    modelZIndexMap.emplace(renderingModel->GetZIndex(), renderingModel.get());
    auto modelPtr = renderingModel.get();
    renderingModels.push_back(std::move(renderingModel));
    modelPtr->SetAssociatedModelId(renderingModels.size() - 1);
    return modelPtr;
}

RenderingModel *GdiRenderer::GetModel(size_t index)
{
    return renderingModels[index].get();
}

RenderingModel * GdiRenderer::CreateModel(Commands createCommand)
{
    switch (createCommand)
    {
        case Commands::RequestRectangle:
        {
            auto model = CreateModel<RectangleModel>();
            model->AddOnMoveSubscriber(*this);
            return model;
        }
        default:
            return nullptr;
    }
}

void GdiRenderer::OnMove(EventMoveInfo e)
{
    auto matches = modelZIndexMap.equal_range(e.GetPrevPosition().z);
    auto model = dynamic_cast<RenderingModel*>(e.GetSrc());
    if (model == nullptr)
        return;

    for(auto it = matches.first; it != matches.second; ++it)
    {
        if(it->second == model)
        {
            modelZIndexMap.erase(it);
            break;
        }
    }
    modelZIndexMap.emplace(e.GetPosition().z, model);
}

void GdiRenderer::SetViewportSize(int width, int height)
{
    SetViewportSize({width, height});
}

void GdiRenderer::SetViewportSize(const glm::ivec2 &size)
{
    std::lock_guard<std::mutex> lock(setViewPortMutex);
    viewPortSize = size;
    UpdateBitmap();
    UpdateSecondaryDC();
}

void GdiRenderer::UpdateBitmap()
{
    DeleteObject(screenBitmap);
    screenBitmap = CreateCompatibleBitmap(windowHdc, viewPortSize.x, viewPortSize.y);
}

void GdiRenderer::OnResize(EventResizeInfo e)
{

}
