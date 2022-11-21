//
// Created by Erik on 19/02/22.
//

#ifndef LII_OPENGLRENDERINGPOOL_H
#define LII_OPENGLRENDERINGPOOL_H
#include <unordered_map>
#include <memory>
#include "RenderingPool.h"
#include "OpenGLRenderer.h"

class Window;
class RenderCommander;

class OpenGLRenderingPool : public RenderingPool
{
public:
    Renderer &Acquire(const RenderCommander &target) override;
    OpenGLRenderingPool(Window &window, OpenGL::RenderingManager &manager);
private:
    OpenGL::RenderingManager& renderingManager;
    std::unordered_map<const RenderCommander*, std::unique_ptr<OpenGLRenderer>> renderers;
    Window& window;
    glm::vec2 translation;
public:
    const glm::vec2 & GetTranslation() const;
    void SetTranslation(const glm::vec2 &translation);
};


#endif //LII_OPENGLRENDERINGPOOL_H
