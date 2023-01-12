//
// Created by Erik on 19/02/22.
//

#ifndef LII_OPENGLRENDERINGPOOL_H
#define LII_OPENGLRENDERINGPOOL_H
#include <unordered_map>
#include <memory>
#include "RenderingPool.h"
#include "OpenGLRenderingApi.h"

class Window;
class RenderCommander;

class OpenGLRenderingPool : public RenderingPool
{
public:
    RenderingApi &Acquire(const RenderCommander &target) override;
    OpenGLRenderingPool(Window &window, OpenGL::RenderingManager &manager);
private:
    OpenGL::RenderingManager& renderingManager;
    std::unordered_map<const RenderCommander*, std::unique_ptr<OpenGLRenderingApi>> renderers;
    Window& window;
    glm::vec4 translation;
public:
    const glm::vec2 & GetTranslation() const;
    void SetTranslation(const glm::vec4 &translation);
};

#endif //LII_OPENGLRENDERINGPOOL_H
