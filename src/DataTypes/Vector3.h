//
// Created by Erik on 22/01/27.
//

#ifndef LII_VECTOR3_H
#define LII_VECTOR3_H


class Vector3
{
public:
    Vector3(Vector3& vector);
    Vector3(float x, float y, float z);
    Vector3();

    float GetX() const;
    void SetX(float x);
    float GetY() const;
    void SetY(float y);
    float GetZ() const;
    void SetZ(float z);
    void SetValue(float x, float y, float z);
    void SetValue(Vector3& vector);

    Vector3 Copy() const;
private:
    float x;
    float y;
    float z;
};


#endif //LII_VECTOR3_H
