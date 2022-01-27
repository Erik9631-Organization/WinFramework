//
// Created by Erik on 1/12/2022.
//

#include "Vector2.h"

float Vector2::GetX() const
{
    return x;
}

void Vector2::SetX(float x)
{
    this->x = x;
}

float Vector2::GetY() const
{
    return y;
}

void Vector2::SetY(float y)
{
    this->y = y;
}

Vector2::Vector2(Gdiplus::Point point) : Vector2((float)point.X, (float)point.Y)
{

}

Vector2::Vector2(Gdiplus::PointF point) : Vector2(point.X, point.Y)
{

}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2::Vector2() : Vector2(0.0f, 0.0f)
{

}

Vector2::Vector2(Gdiplus::SizeF size) : Vector2(size.Width, size.Height)
{

}

Vector2::Vector2(Gdiplus::Size size) : Vector2((float)size.Width, (float)size.Height)
{

}

void Vector2::SetValue(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vector2::SetValue(Gdiplus::Size size)
{
    this->x = (float)size.Width;
    this->y = (float)size.Height;
}

void Vector2::SetValue(Gdiplus::SizeF size)
{
    this->x = size.Width;
    this->y = size.Height;
}

void Vector2::SetValue(Gdiplus::Point point)
{
    this->x = (float)point.X;
    this->y = (float)point.Y;
}

void Vector2::SetValue(Gdiplus::PointF point)
{
    this->x = point.X;
    this->y = point.Y;
}
