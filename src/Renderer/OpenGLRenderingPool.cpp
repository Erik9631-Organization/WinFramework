//
// Created by Erik on 19/02/22.
//

#include "OpenGLRenderingPool.h"
#include "Renderable.h"
#include "OpenGLRenderer.h"
OpenGLRenderingPool* OpenGLRenderingPool::rendererPool = new OpenGLRenderingPool();

OpenGLRenderingPool &OpenGLRenderingPool::GetRenderPool()
{
    return *rendererPool;
}


Renderer &OpenGLRenderingPool::Acquire(const Renderable &target)
{
    auto renderableIt = renderers.find(&target);
    if(renderableIt != renderers.end())
        return *renderableIt->second;
    //Not found, new one needs to be created
    renderers.insert({&target, std::make_unique<OpenGLRenderer>()});
    return *renderers[&target];
}
