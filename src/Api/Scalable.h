//
// Created by Erik on 20/03/22.
//

#ifndef LII_SCALABLE_H
#define LII_SCALABLE_H
#include <glm.hpp>

class Scalable
{
public:
    virtual void Scale(const glm::vec3& scale) = 0;
    virtual void SetScale(const glm::vec3& scale) = 0;
    virtual const glm::vec3& GetScale() = 0;
};


#endif //LII_SCALABLE_H
