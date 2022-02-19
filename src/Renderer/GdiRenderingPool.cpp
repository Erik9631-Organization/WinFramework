//
// Created by Erik on 19/02/22.
//

#include "GdiRenderingPool.h"

Renderer &GdiRenderingPool::Acquire(const Renderable &target)
{
    return *renderer;
}

GdiRenderingPool::GdiRenderingPool(Renderer *renderer)
{
    this->renderer = renderer;
}
