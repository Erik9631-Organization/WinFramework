//
// Created by Erik on 19/02/22.
//

#ifndef LII_OPENGLRENDERINGPOOL_H
#define LII_OPENGLRENDERINGPOOL_H
#include <unordered_map>
#include <memory>
#include "RenderingPool.h"

class OpenGLRenderer;
class Renderable;

class OpenGLRenderingPool : public RenderingPool
{
public:
    static OpenGLRenderingPool& GetRenderPool();
    Renderer &Acquire(const Renderable &target) override;
private:
    OpenGLRenderingPool() = default;
    OpenGLRenderingPool(OpenGLRenderingPool &&) = default;
    OpenGLRenderingPool(OpenGLRenderingPool &) = default;
    static OpenGLRenderingPool* rendererPool;
    std::unordered_map<const Renderable*, std::unique_ptr<OpenGLRenderer>> renderers;
};


#endif //LII_OPENGLRENDERINGPOOL_H
