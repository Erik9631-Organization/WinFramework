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

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2::Vector2() : Vector2(0.0f, 0.0f)
{

}

void Vector2::SetValue(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2::Vector2(Vector2 &vector)
{
    this->x = vector.GetX();
    this->y = vector.GetY();
}

void Vector2::SetValue(Vector2 &vector)
{
    this->x = vector.GetX();
    this->y = vector.GetY();
}

Vector2 Vector2::Copy()
{
    return {this->GetX(), this->GetY()};
}
