//
// Created by erik9 on 5/14/2023.
//

#include "WindowsBufferRenderer.h"
#include "EventCoreLifecycleInfo.h"
#include "ConcurrentShapeRenderer.h"
#include "AggShapeRenderer.h"
#include "ShapeRenderer.h"
#include "Injector.hpp"

void WindowsBufferRenderer::OnCoreInit(const EventCoreLifecycleInfo &e)
{

}

void WindowsBufferRenderer::OnCoreStart(const EventCoreLifecycleInfo &e)
{
    core = dynamic_cast<WindowsCore*>(e.GetCore());
    if(core == nullptr)
        std::cout << "WindowsBufferRenderer::OnCoreStart: core is not a WindowsCore instance\n" << std::endl;
    screenSize = core->GetCombinedScreenSize();
    viewportSize = core->GetWindow()->GetSize();
    CreateGraphicsBuffer();
}

void WindowsBufferRenderer::OnCoreStop(const EventCoreLifecycleInfo &e)
{

}

void WindowsBufferRenderer::OnCoreDestroy(const EventCoreLifecycleInfo &e)
{

}

void WindowsBufferRenderer::DrawFragment(const glm::ivec3 &position, const glm::ivec4 &color)
{
    unsigned int hexColor = (color.a << 24) | (color.r << 16) | (color.g << 8) |  color.b;
    back->DrawFragment(position.x, position.y, hexColor);
}

void WindowsBufferRenderer::DeleteSecondaryDc()
{
    if(secondaryHdc != nullptr)
        DeleteDC(secondaryHdc);
}

void WindowsBufferRenderer::CreateSecondaryDc()
{
    if(windowHdc == nullptr)
        return;
    DeleteSecondaryDc();
    secondaryHdc = CreateCompatibleDC(windowHdc);
}


void WindowsBufferRenderer::SwapScreenBuffer()
{
    if(front == nullptr || back == nullptr)
        return;
    std::swap(front, back); // We can now safely swap the buffers and rendering should continue on the other buffer.
    SelectObject(secondaryHdc, front->GetBitmap()); // Associate the front buffer with the secondaryHdc
    BitBlt(windowHdc, 0, 0, viewportSize.x, viewportSize.y, secondaryHdc, 0, 0, SRCCOPY);
    ReleaseRenderers();
}

void WindowsBufferRenderer::SetViewportSize(const glm::ivec2 &size)
{
    viewportSize = size;
}

void WindowsBufferRenderer::CreateGraphicsBuffer()
{
    if(core == nullptr)
    {
        std::cout << "WindowsBufferRenderer::CreateGraphicsBuffer: core doesn't exist" << std::endl;
        return;
    }

    windowHdc = core->GetHdc();
    CreateSecondaryDc();
    CreateBitmap();
}

void WindowsBufferRenderer::CreateBitmap()
{
    if(front != nullptr && back != nullptr)
       return;
    front = new BitmapManager(screenSize, secondaryHdc);
    back = new BitmapManager(screenSize, secondaryHdc);
    front->SetSize(screenSize, secondaryHdc);
    back->SetSize(screenSize, secondaryHdc);
}


WindowsBufferRenderer::~WindowsBufferRenderer()
{
    delete front;
    delete back;
}

const glm::ivec2 &WindowsBufferRenderer::GetViewportSize() const
{
    return viewportSize;
}

ShapeRenderer &WindowsBufferRenderer::AcquireShapeRenderer()
{
    auto* shapeRenderer = LiiInjector::Injector::GetInstance().ResolveTransient<ShapeRenderer>().release();
    shapeRenderer->SetScreenBuffer(*this);
    renderer.emplace_back(shapeRenderer);
    return *shapeRenderer;
}

void WindowsBufferRenderer::ReleaseRenderers()
{
    for(auto* shapeRenderer : renderer)
        delete shapeRenderer;
    renderer.clear();
}

Lii::DataTypes::Buffer<unsigned int> WindowsBufferRenderer::GetScreenBuffer()
{
    return {back->GetSize().x, back->GetSize().y, back->GetBuffer()};
}

unsigned int WindowsBufferRenderer::CreateColor(const glm::ivec4 &color)
{
    unsigned int hexColor = (color.a << 24) | (color.r << 16) | (color.g << 8) |  color.b;
    return hexColor;
}
