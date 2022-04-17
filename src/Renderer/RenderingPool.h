//
// Created by Erik on 19/02/22.
//

#ifndef LII_RENDERINGPOOL_H
#define LII_RENDERINGPOOL_H
class Renderer;
class RenderCommander;

class RenderingPool
{
public:
    virtual Renderer& Acquire(const RenderCommander &target) = 0;
};


#endif //LII_RENDERINGPOOL_H
