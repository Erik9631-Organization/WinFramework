//
// Created by Erik on 20/03/22.
//

#ifndef LII_ROTATABLE_H
#define LII_ROTATABLE_H
#include <glm.hpp>

class Rotatable
{
public:
    virtual void Rotate(const float& angle, const glm::vec3& axis) = 0;
};


#endif //LII_ROTATABLE_H
