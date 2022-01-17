//
// Created by Erik on 1/12/2022.
//

#include "Vector2d.h"

float Vector2d::GetX() const
{
    return x;
}

void Vector2d::SetX(float x)
{
    this->x = x;
}

float Vector2d::GetY() const
{
    return y;
}

void Vector2d::SetY(float y)
{
    this->y = y;
}

Vector2d::Vector2d(Gdiplus::Point point) : Vector2d((float)point.X, (float)point.Y)
{

}

Vector2d::Vector2d(Gdiplus::PointF point) : Vector2d(point.X, point.Y)
{

}

Vector2d::Vector2d(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2d::Vector2d() : Vector2d(0.0f, 0.0f)
{

}

Vector2d::Vector2d(Gdiplus::SizeF size) : Vector2d(size.Width, size.Height)
{

}

Vector2d::Vector2d(Gdiplus::Size size) : Vector2d((float)size.Width, (float)size.Height)
{

}

void Vector2d::SetValue(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vector2d::SetValue(Gdiplus::Size size)
{
    this->x = (float)size.Width;
    this->y = (float)size.Height;
}

void Vector2d::SetValue(Gdiplus::SizeF size)
{
    this->x = size.Width;
    this->y = size.Height;
}

void Vector2d::SetValue(Gdiplus::Point point)
{
    this->x = (float)point.X;
    this->y = (float)point.Y;
}

void Vector2d::SetValue(Gdiplus::PointF point)
{
    this->x = point.X;
    this->y = point.Y;
}
