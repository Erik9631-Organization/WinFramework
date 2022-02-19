//
// Created by Erik on 19/02/22.
//

#include "OpenGLRendererPool.h"
#include "Renderable.h"
#include "OpenGLRenderer.h"
OpenGLRendererPool* OpenGLRendererPool::rendererPool = new OpenGLRendererPool();

OpenGLRendererPool &OpenGLRendererPool::GetRenderPool()
{
    return *rendererPool;
}

OpenGLRenderer &OpenGLRendererPool::AquireRenderer(const Renderable &renderable)
{
    auto renderableIt = renderers.find(&renderable);
    if(renderableIt != renderers.end())
        return *renderableIt->second;
    //Not found, new one needs to be created
    renderers.insert({&renderable, std::make_unique<OpenGLRenderer>()});
    return *renderers[&renderable];
}
