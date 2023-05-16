//
// Created by erik9 on 5/14/2023.
//

#include "WindowsBufferRenderer.h"
#include "EventCoreLifecycleInfo.h"

void WindowsBufferRenderer::OnCoreInit(const EventCoreLifecycleInfo &e)
{

}

void WindowsBufferRenderer::OnCoreStart(const EventCoreLifecycleInfo &e)
{
    core = dynamic_cast<WindowsCore*>(e.GetCore());
    if(core == nullptr)
        std::cout << "WindowsBufferRenderer::OnCoreStart: core is not a WindowsCore instance\n" << std::endl;
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
    unsigned int hexColor = (color.r << 24) | (color.g << 16) | (color.b << 8) | (color.a);
    front.buffer[position.y * viewportSize.x + position.x] = 0xffffffff;
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
    SelectObject(secondaryHdc, front.bitmap); // Associate the front buffer with the secondaryHdc
    std::swap(front, back); // We can now safely swap the buffers and rendering should continue on the other buffer.
    BitBlt(windowHdc, 0, 0, viewportSize.x, viewportSize.y, secondaryHdc, 0, 0, SRCCOPY);
}

void WindowsBufferRenderer::SetViewportSize(const glm::ivec2 &size)
{
    viewportSize = size;
    CreateSecondaryDc();
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
    BITMAPINFO bitmapInfo{};
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = viewportSize.x;
    bitmapInfo.bmiHeader.biHeight = viewportSize.y;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    front.bitmap = CreateDIBSection(windowHdc, &bitmapInfo, DIB_RGB_COLORS, (void**)&front.buffer, nullptr, 0);
    std::cout <<  "Front bitmap " <<GetLastError() << std::endl;
    back.bitmap = CreateDIBSection(windowHdc, &bitmapInfo, DIB_RGB_COLORS, (void**)&back.buffer, nullptr, 0);
    std::cout << "Back bitmap " << GetLastError() << std::endl;
}
