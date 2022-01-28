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
    Vector2(Vector2& vector);
    Vector2(float x, float y);
    Vector2();

    float GetX() const;
    void SetX(float x);
    float GetY() const;
    void SetY(float y);
    void SetValue(float x, float y);
    void SetValue(Vector2& vector);
    Vector2 Copy();

private:
    float x;
    float y;
};


#endif //GRAPHICS_VECTOR2D_H
