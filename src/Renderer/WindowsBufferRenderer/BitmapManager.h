//
// Created by erik9 on 5/16/2023.
//

#ifndef LII_BITMAPMANAGER_H
#define LII_BITMAPMANAGER_H
#include <windows.h>
#include <vector>
#include <memory>
#include "glm.hpp"
#include "agg_renderer_base.h"
#include "agg_pixfmt_rgba.h"

class BitmapManager
{
private:
    std::unique_ptr<agg::rendering_buffer> aggBuffer;
    std::unique_ptr<agg::pixfmt_bgra32> pixelFormat;
    std::unique_ptr<agg::renderer_base<agg::pixfmt_bgra32>> renderBase;
    HBITMAP bitmap = nullptr;
    unsigned int *buffer = nullptr;
    void Release();
    void CreateBitmap(HDC hdc);
    glm::ivec2 size{0};
public:
    BitmapManager(const glm::ivec2 &size, HDC hdc);

    void SetSize(const glm::ivec2 &size, HDC hdc);

    void DrawFragment(unsigned int x, unsigned int y, unsigned int hexColor);

    [[nodiscard]] const glm::ivec2 & GetSize();

    [[nodiscard]] unsigned int *GetBuffer() const;

    [[nodiscard]] HBITMAP GetBitmap() const;

    ~BitmapManager();
};

#endif //LII_BITMAPMANAGER_H
