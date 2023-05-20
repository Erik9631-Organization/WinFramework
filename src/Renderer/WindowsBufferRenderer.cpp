//
// Created by erik9 on 5/14/2023.
//

#include "WindowsBufferRenderer.h"
#include "EventCoreLifecycleInfo.h"
#include "Tracy.hpp"

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
    ZoneScoped;
    unsigned int hexColor = (color.a << 24) | (color.r << 16) | (color.g << 8) |  color.b;
    back->DrawFragment(position.x, position.y, hexColor);
}


void WindowsBufferRenderer::DeleteSecondaryDc()
{
    ZoneScoped;
    if(secondaryHdc != nullptr)
        DeleteDC(secondaryHdc);
}

void WindowsBufferRenderer::CreateSecondaryDc()
{
    ZoneScoped;
    if(windowHdc == nullptr)
        return;
    DeleteSecondaryDc();
    secondaryHdc = CreateCompatibleDC(windowHdc);
}


void WindowsBufferRenderer::SwapScreenBuffer()
{
    ZoneScoped;
    std::swap(front, back); // We can now safely swap the buffers and rendering should continue on the other buffer.
    SelectObject(secondaryHdc, front->GetBitmap()); // Associate the front buffer with the secondaryHdc
    BitBlt(windowHdc, 0, 0, viewportSize.x, viewportSize.y, secondaryHdc, 0, 0, SRCCOPY);
}

void WindowsBufferRenderer::SetViewportSize(const glm::ivec2 &size)
{
    viewportSize = size;
}

void WindowsBufferRenderer::CreateGraphicsBuffer()
{
    ZoneScoped;
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
    ZoneScoped;
    front->SetSize(screenSize, secondaryHdc);
    back->SetSize(screenSize, secondaryHdc);
}

WindowsBufferRenderer::WindowsBufferRenderer() :
    front(new BitmapManager(glm::ivec2(0, 0), nullptr)),
    back(new BitmapManager(glm::ivec2(0, 0), nullptr))
{

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
