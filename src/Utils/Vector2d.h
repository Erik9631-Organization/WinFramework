//
// Created by Erik on 1/12/2022.
//

#ifndef GRAPHICS_VECTOR2D_H
#define GRAPHICS_VECTOR2D_H
#include <Windows.h>
#include <gdiplus.h>

class Vector2d
{
public:
    Vector2d(Gdiplus::Size size);
    Vector2d(Gdiplus::SizeF size);
    Vector2d(Gdiplus::Point point);
    Vector2d(Gdiplus::PointF point);
    Vector2d(float x, float y);
    Vector2d();

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
