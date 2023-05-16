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
    unsigned int hexColor = (color.a << 24) | (color.r << 16) | (color.g << 8) |  color.b;
    for(int i = 0; i < 2000; i++)
        front.buffer[i] = hexColor;

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
    CreateBitmap();
}

void WindowsBufferRenderer::CreateBitmap()
{
    BITMAPINFO bitmapInfo{};
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = viewportSize.x;
    bitmapInfo.bmiHeader.biHeight = -viewportSize.y;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    auto frontBitmap = CreateDIBSection(windowHdc, &bitmapInfo, DIB_RGB_COLORS, (void**)&front.buffer, nullptr, 0);
    auto backBitmap = CreateDIBSection(windowHdc, &bitmapInfo, DIB_RGB_COLORS, (void**)&back.buffer, nullptr, 0);
    if(front.buffer == nullptr || back.buffer == nullptr)
    {
        std::cout << "WindowsBufferRenderer::CreateBitmap: failed to create bitmap" << std::endl;
        return;
    }
}

void WindowsBufferRenderer::CopyOldBitmapToNew(Bitmap &newBitmap, Bitmap &oldBitmap)
{

}
