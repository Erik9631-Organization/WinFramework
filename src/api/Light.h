//
// Created by Erik on 26/06/22.
//

#ifndef LII_LIGHT_H
#define LII_LIGHT_H
#include <glm.hpp>

class Light
{
public:
    virtual void SetEnabled(const bool& State) = 0;
    virtual const bool & GetEnabled() const = 0;
    virtual const glm::vec4 GetColor() const = 0;
    virtual void SetColor(const glm::vec4& color) = 0;
};

#endif //LII_LIGHT_H
