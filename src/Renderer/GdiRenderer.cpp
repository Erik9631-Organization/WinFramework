//
// Created by Erik on 22/01/24.
//
#include "GdiRenderer.h"
#include "Core/Windows/WindowsCore.h"
#include "Window.h"
#include "RenderEventInfo.h"
#include "EventResizeInfo.h"
#include "GdiRenderingApi.h"
#include <execution>
#include <future>
#include <chrono>
#include "GdiRenderingPool.h"
#include "ApplicationController.h"
#include "RectangleModel.h"
#include <iostream>
using namespace std;
using namespace chrono;
using namespace Gdiplus;

ULONG GdiRenderer::token = 0;
Gdiplus::GdiplusStartupOutput GdiRenderer::output = {};

void GdiRenderer::Render()
{
    for (auto& model : modelZIndexMap)
        model.second->Redraw();
}

void GdiRenderer::CleanBackBuffer()
{
    ReleaseDC(windowHandle, secondaryDc);
    DeleteDC(secondaryDc);
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


HDC GdiRenderer::GetSecondaryDC()
{
    secondaryDc = CreateCompatibleDC(windowHdc);
    SelectObject(secondaryDc, secondaryBitmap);
    return secondaryDc;
}

//TODO should be handled by redraw
void GdiRenderer::OnResize(EventResizeInfo e)
{
//    auto size = Size((int)e.GetSize().x, (int)e.GetSize().y);
//    secondaryBitmap = CreateCompatibleBitmap(GetWindowDC(windowHandle), size.Width, size.Height);
}

void GdiRenderer::OnInit(Core &coreWindowFrame)
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
}

void GdiRenderer::OnDestroy(Core &coreWindow)
{
    CleanBackBuffer();
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

std::unique_ptr<RenderingApi> GdiRenderer::AcquireRenderingApi()
{
    auto graphics = std::make_unique<Graphics>(secondaryDc);
    auto renderer = new GdiRenderingApi(std::move(graphics));
    return std::unique_ptr<RenderingApi>(renderer);
}

void GdiRenderer::SwapScreenBuffer()
{
    BitBlt(windowHdc, 0, 0, windowsCore->GetWrapperFrame()->GetWidth(), windowsCore->GetWrapperFrame()->GetHeight(), secondaryDc, 0, 0, MERGECOPY);
    CleanBackBuffer(); // Cleans only the SecondaryDC, as the window has permanent DC
    GetSecondaryDC();
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
