//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORT2_H
#define LII_VIEWPORT2_H
#include "glm.hpp"

class Viewport2
{
public:
    virtual void SetViewportSize(const glm::vec4&) = 0;
    virtual void SetViewportPosition(const glm::vec4&) = 0;
    virtual glm::vec4 & GetViewportSize() = 0;
    virtual glm::vec4 & GetViewportPosition() = 0;
    virtual void ResetViewport() = 0;
};

#endif //LII_VIEWPORT2_H
