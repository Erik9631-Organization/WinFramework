//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_GRAPHICSVIEWPORT_H
#define LII_GRAPHICSVIEWPORT_H
#include "glm.hpp"

class GraphicsViewport
{
public:
    virtual void SetViewPortSize(const glm::vec4&) = 0;
    virtual void SetViewPortPosition(const glm::vec4&) = 0;
    virtual glm::vec4 & GetViewPortSize() = 0;
    virtual glm::vec4 & GetViewPortPosition() = 0;
    virtual void ResetViewPort() = 0;
};

#endif //LII_GRAPHICSVIEWPORT_H
