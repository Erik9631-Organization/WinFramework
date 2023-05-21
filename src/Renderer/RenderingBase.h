//
// Created by erik9 on 5/14/2023.
//

#ifndef LII_RENDERINGBASE_H
#define LII_RENDERINGBASE_H

#include <glm.hpp>
#include "ShapeRenderer.h"


class RenderingBase
{
public:
    virtual void SwapScreenBuffer() = 0;
    virtual void SetViewportSize(const glm::ivec2& size) = 0;
    virtual ShapeRenderer& AcquireShapeRenderer() = 0;
    [[nodiscard]] virtual const glm::ivec2& GetViewportSize() const = 0;
    virtual ~RenderingBase() = default;
};
#endif //LII_RENDERINGBASE_H
