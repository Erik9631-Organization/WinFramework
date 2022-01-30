//
// Created by Erik on 29/01/22.
//

#ifndef LII_VECTOR2INT_H
#define LII_VECTOR2INT_H

class Vector2;

class Vector2Int
{
public:
    Vector2Int(const Vector2Int& vector);
    Vector2Int(const Vector2& vector);
    Vector2Int(int x, int y);
    Vector2Int();

    int GetX() const;
    void SetX(float x);
    int GetY() const;
    void SetY(int y);
    void SetValue(int x, int y);
    void SetValue(Vector2Int& vector);
    Vector2Int Copy();
    Vector2Int& operator +(const Vector2Int& ref);

private:
    int x;
    int y;
};

#endif //LII_VECTOR2INT_H
