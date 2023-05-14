//
// Created by Erik on 19/02/22.
//

#include "GdiRenderingPool.h"

ShapeRenderer &GdiRenderingPool::Acquire(const RenderCommander &target)
{
    return *renderer;
}

GdiRenderingPool::GdiRenderingPool(ShapeRenderer *renderer)
{
    this->renderer = renderer;
}
