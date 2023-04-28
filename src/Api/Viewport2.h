//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORT2_H
#define LII_VIEWPORT2_H
#include "glm.hpp"
#include "Viewport2Subject.h"

class Viewport2 : public Viewport2Subject
{
public:
    virtual void SetViewportSize(const glm::vec4&) = 0;
    virtual void SetViewportPosition(const glm::vec3 &) = 0;
    virtual const glm::vec4 & GetViewportSize() = 0;
    virtual const glm::vec3 & GetViewportPosition() = 0;
    virtual void ResetViewport() = 0;
    [[nodiscard]] virtual bool IsViewportSet() const = 0;
};

#endif //LII_VIEWPORT2_H
