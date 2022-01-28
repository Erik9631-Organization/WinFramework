//
// Created by Erik on 22/01/27.
//

#include "Vector4.h"

float Vector4::GetX() const
{
    return x;
}

void Vector4::SetX(float x)
{
    this->x = x;
}

float Vector4::GetY() const
{
    return y;
}

void Vector4::SetY(float y)
{
    this->y = y;
}

Vector4::Vector4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4::Vector4() : Vector4(0.0f, 0.0f, 0.0f, 0.0f)
{

}

void Vector4::SetValue(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector4::Vector4(Vector4 &vector)
{
    this->x = vector.GetX();
    this->y = vector.GetY();
    this->z = vector.GetZ();
    this->w = vector.GetW();
}

void Vector4::SetValue(Vector4 &vector)
{
    this->x = vector.GetX();
    this->y = vector.GetY();
}

Vector4 Vector4::Copy() const
{
    return {this->GetX(), this->GetY(), this->GetZ(), this->GetW()};
}

float Vector4::GetZ() const
{
    return z;
}

void Vector4::SetZ(float z)
{
    this->z = z;
}

float Vector4::GetW() const
{
    return w;
}

void Vector4::SetW(float z)
{
    this->z = z;
}
