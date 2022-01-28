//
// Created by Erik on 22/01/27.
//

#include "Vector3.h"

float Vector3::GetX() const
{
    return x;
}

void Vector3::SetX(float x)
{
    this->x = x;
}

float Vector3::GetY() const
{
    return y;
}

void Vector3::SetY(float y)
{
    this->y = y;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3() : Vector3(0.0f, 0.0f, 0.0f)
{

}

void Vector3::SetValue(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(Vector3 &vector)
{
    this->x = vector.GetX();
    this->y = vector.GetY();
    this->z = vector.GetZ();
}

void Vector3::SetValue(Vector3 &vector)
{
    this->x = vector.GetX();
    this->y = vector.GetY();
}

Vector3 Vector3::Copy() const
{
    return {this->GetX(), this->GetY(), this->GetZ()};
}

float Vector3::GetZ() const
{
    return z;
}

void Vector3::SetZ(float z)
{
    this->z = z;
}