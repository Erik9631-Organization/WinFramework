//
// Created by Erik on 1/12/2022.
//

#include "Vector2.h"
#include "Vector2Int.h"
#include "CoreWindow.h"

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

Vector2::Vector2(const Vector2 &vector)
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

Vector2 Vector2::operator+(const Vector2 &ref)
{
    return {this->x + ref.GetX(), this->y + ref.GetY()};
}

Vector2::Vector2(const Vector2Int &vector)
{
    this->x = vector.GetX();
    this->y = vector.GetY();
}

Vector2 Vector2::operator-(const Vector2 &ref)
{
   // CoreWindow::ConsoleWrite(to_string(ref.GetX()) + " " + to_string(ref.GetY()) + " - " + to_string(this->x) + " " + to_string(this->y));
    return {this->x - ref.GetX(), this->y - ref.GetY()};
}
