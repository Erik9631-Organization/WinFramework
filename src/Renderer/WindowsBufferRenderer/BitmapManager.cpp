//
// Created by erik9 on 5/16/2023.
//

#include "BitmapManager.h"
#include "EventResizeInfo.h"

void BitmapManager::Release()
{
    if(bitmap != nullptr)
        DeleteObject(bitmap);
    bitmap = nullptr;
    buffer = nullptr;
}

BitmapManager::~BitmapManager()
{
    Release();
}

BitmapManager::BitmapManager(const glm::ivec2 &size, HDC hdc)
{
    this->size = size;
    CreateBitmap(hdc);
}


void BitmapManager::SetSize(const glm::ivec2 &size, HDC hdc)
{
    this->size = size;
    CreateBitmap(hdc);
}

const glm::ivec2 & BitmapManager::GetSize()
{
    return size;
}

void BitmapManager::CreateBitmap(HDC hdc)
{
    BITMAPINFO bitmapInfo{};
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = size.x;
    bitmapInfo.bmiHeader.biHeight = -size.y;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    Release();
    bitmap = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, (void**)&buffer, nullptr, 0);
    aggBuffer = std::make_unique<agg::rendering_buffer>(reinterpret_cast<unsigned char*>(buffer), size.x, size.y, size.x * sizeof (unsigned int));
    pixelFormat = std::make_unique<agg::pixfmt_bgra32>(*aggBuffer);
}

unsigned int *BitmapManager::GetBuffer() const
{
    return reinterpret_cast<unsigned int *>(buffer);
}

HBITMAP BitmapManager::GetBitmap() const
{
    return bitmap;
}

void BitmapManager::DrawFragment(unsigned int x, unsigned int y, unsigned int hexColor)
{
    if(buffer == nullptr)
        return;
    if(x >= size.x || y >= size.y)
        return;
    buffer[y * size.x + x] = hexColor;
}
