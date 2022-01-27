//
// Created by Erik on 1/12/2022.
//

#ifndef GRAPHICS_VECTOR2D_H
#define GRAPHICS_VECTOR2D_H
#include <Windows.h>
#include <gdiplus.h>

class Vector2
{
public:
    Vector2(Gdiplus::Size size);
    Vector2(Gdiplus::SizeF size);
    Vector2(Gdiplus::Point point);
    Vector2(Gdiplus::PointF point);
    Vector2(float x, float y);
    Vector2();

    float GetX() const;
    void SetX(float x);
    float GetY() const;
    void SetY(float y);
    void SetValue(float x, float y);
    void SetValue(Gdiplus::Size size);
    void SetValue(Gdiplus::SizeF size);
    void SetValue(Gdiplus::Point point);
    void SetValue(Gdiplus::PointF point);

private:
    float x;
    float y;
};


#endif //GRAPHICS_VECTOR2D_H
