//
// Created by Erik on 29/01/22.
//

#include "Vector2Int.h"
#include "Vector2.h"

int Vector2Int::GetX() const
{
    return x;
}

void Vector2Int::SetX(int x)
{
    this->x = x;
}

int Vector2Int::GetY() const
{
    return y;
}

void Vector2Int::SetY(int y)
{
    this->y = y;
}

Vector2Int::Vector2Int(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2Int::Vector2Int() : Vector2Int(0.0f, 0.0f)
{

}

void Vector2Int::SetValue(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2Int::Vector2Int(const Vector2Int &vector)
{
    this->x = vector.GetX();
    this->y = vector.GetY();
}

void Vector2Int::SetValue(Vector2Int &vector)
{
    this->x = vector.GetX();
    this->y = vector.GetY();
}

Vector2Int Vector2Int::Copy()
{
    return {this->GetX(), this->GetY()};
}

Vector2Int &Vector2Int::operator+(const Vector2Int &ref)
{
    this->x += ref.GetX();
    this->y += ref.GetY();
    return *this;
}

Vector2Int::Vector2Int(const Vector2 &vector)
{
    this->x = (int)(vector.GetX());
    this->y = (int)(vector.GetY());
}
