//
// Created by Erik on 19/02/22.
//

#include "OpenGLRenderingPool.h"
#include "api/RenderCommander.h"
#include "OpenGLShapeRenderer.h"
#include "Window.h"

ShapeRenderer &OpenGLRenderingPool::Acquire(const RenderCommander &target)
{
    auto renderableIt = renderers.find(&target);
    if(renderableIt != renderers.end())
    {
        OpenGLShapeRenderer& renderer = *renderableIt->second;
        renderer.Translate(translation);
        return *renderableIt->second;
    }

    //Not found, new one needs to be created
    //CRASH1
    renderers.insert({&target, std::make_unique<OpenGLShapeRenderer>(window, renderingManager)});
    OpenGLShapeRenderer& renderer = *renderers[&target];
    renderer.Translate(translation);
    return *renderers[&target];
}

OpenGLRenderingPool::OpenGLRenderingPool(Window &window, OpenGL::RenderingManager &manager) : window(window), renderingManager(manager)
{
}

const glm::vec2 & OpenGLRenderingPool::GetTranslation() const
{
    return translation;
}

void OpenGLRenderingPool::SetTranslation(const glm::vec3 &translation)
{
    this->translation = translation;
}
