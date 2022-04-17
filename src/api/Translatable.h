//
// Created by Erik on 20/03/22.
//

#ifndef LII_TRANSLATABLE_H
#define LII_TRANSLATABLE_H
#include <glm.hpp>

class Translatable
{
public:
    virtual void Translate(const glm::vec3& translation) = 0;
};


#endif //LII_TRANSLATABLE_H
