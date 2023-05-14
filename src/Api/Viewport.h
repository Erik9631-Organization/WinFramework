//
// Created by erik9 on 4/23/2023.
//

#ifndef LII_VIEWPORT_H
#define LII_VIEWPORT_H
#include "glm.hpp"
#include "ViewportSubject.h"

class Viewport : public ViewportSubject
{
public:
    virtual void SetViewportSize(const glm::vec3 &) = 0;
    virtual void SetViewportPosition(const glm::vec3 &) = 0;
    virtual const glm::vec3 & GetViewportSize() = 0;
    virtual const glm::vec3 & GetViewportPosition() = 0;
    virtual void ResetViewport() = 0;
    [[nodiscard]] virtual bool IsViewportSet() const = 0;
};

#endif //LII_VIEWPORT_H
