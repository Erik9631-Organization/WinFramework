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
    cout << "Rendering" << endl;
    for (auto it = modelZIndexMap.rbegin(); it != modelZIndexMap.rend(); ++it)
        it->second->Redraw();
}

void GdiRenderer::CleanDeviceContext()
{
    DeleteDC(secondaryDc);
    GetLastError();
}

void GdiRenderer::AssignGraphicsToNodes(MultiTree<std::unique_ptr<UiElement>> &node, Gdiplus::Region& clippingRegion)
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

void GdiRenderer::UpdateSecondaryDC()
{
    CleanDeviceContext();
    cout <<"Width: " << GetDeviceCaps(windowHdc, HORZRES) << endl;
    cout <<"Height: " << GetDeviceCaps(windowHdc, VERTRES) << endl;
    secondaryDc = CreateCompatibleDC(windowHdc);
    SelectObject(secondaryDc, screenBitmap);
}

//TODO should be handled by redraw
void GdiRenderer::OnResize(EventResizeInfo e)
{
//    auto size = Size((int)e.GetSize().x, (int)e.GetSize().y);
//    screenBitmap = CreateCompatibleBitmap(GetWindowDC(windowHandle), size.Width, size.Height);
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
    cout << "Swapping" << endl;
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

//Can be called from any thread---Has to be thread safe.
void GdiRenderer::SetViewportSize(const glm::ivec2 &size)
{
    std::lock_guard<std::mutex> lock(setViewPortMutex);
    cout << "Viewport setting" << std::endl;
    viewPortSize = size;
    UpdateBitmap();
    UpdateSecondaryDC();
    cout << "Viewport set" << std::endl;
}

void GdiRenderer::UpdateBitmap()
{
    DeleteObject(screenBitmap);
    screenBitmap = CreateCompatibleBitmap(windowHdc, viewPortSize.x, viewPortSize.y);
}
