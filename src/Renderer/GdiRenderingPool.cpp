//
// Created by Erik on 19/02/22.
//

#include "GdiRenderingPool.h"

RenderingApi &GdiRenderingPool::Acquire(const RenderCommander &target)
{
    return *renderer;
}

GdiRenderingPool::GdiRenderingPool(RenderingApi *renderer)
{
    this->renderer = renderer;
}
