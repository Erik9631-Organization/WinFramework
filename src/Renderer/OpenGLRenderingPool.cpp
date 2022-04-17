//
// Created by Erik on 19/02/22.
//

#include "OpenGLRenderingPool.h"
#include "api/RenderCommander.h"
#include "OpenGLRenderer.h"
#include "Window.h";

Renderer &OpenGLRenderingPool::Acquire(const RenderCommander &target)
{
    auto renderableIt = renderers.find(&target);
    if(renderableIt != renderers.end())
    {
        OpenGLRenderer& renderer = *renderableIt->second;
        renderer.Translate(translation);
        return *renderableIt->second;
    }

    //Not found, new one needs to be created
    renderers.insert({&target, std::make_unique<OpenGLRenderer>(window)});
    OpenGLRenderer& renderer = *renderers[&target];
    renderer.Translate(translation);
    return *renderers[&target];
}

OpenGLRenderingPool::OpenGLRenderingPool(Window &window) : window(window)
{

}

const Vector2 &OpenGLRenderingPool::GetTranslation() const
{
    return translation;
}

void OpenGLRenderingPool::SetTranslation(const Vector2 &translation)
{
    this->translation = translation;
}
