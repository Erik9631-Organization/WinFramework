//
// Created by Erik on 22/01/27.
//

#ifndef LII_VECTOR4_H
#define LII_VECTOR4_H


class Vector4
{
public:
    Vector4(Vector4& vector);
    Vector4(const Vector4& vector);
    Vector4(float x, float y, float z, float w);
    Vector4();

    float GetX() const;
    void SetX(float x);
    float GetY() const;
    void SetY(float y);
    float GetZ()const;
    void SetZ(float z);
    float GetW()const;
    void SetW(float z);
    void SetValue(float x, float y, float z, float w);
    void SetValue(Vector4& vector);

    Vector4 Copy() const;
private:
    float x;
    float y;
    float z;
    float w;
};


#endif //LII_VECTOR4_H
