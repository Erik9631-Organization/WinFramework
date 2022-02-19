//
// Created by Erik on 19/02/22.
//

#ifndef LII_RENDERINGPOOL_H
#define LII_RENDERINGPOOL_H
class Renderer;
class Renderable;

class RenderingPool
{
public:
    virtual Renderer& Acquire(const Renderable &target) = 0;
};


#endif //LII_RENDERINGPOOL_H
