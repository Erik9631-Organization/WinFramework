//
// Created by Erik on 19/02/22.
//

#ifndef LII_OPENGLRENDERINGPOOL_H
#define LII_OPENGLRENDERINGPOOL_H
#include <unordered_map>
#include <memory>
#include "RenderingPool.h"
#include "OpenGLRenderer.h"
#include "Vector2.h"
class Window;
class Renderable;

class OpenGLRenderingPool : public RenderingPool
{
public:
    Renderer &Acquire(const Renderable &target) override;
    OpenGLRenderingPool(Window& window);
private:
    std::unordered_map<const Renderable*, std::unique_ptr<OpenGLRenderer>> renderers;
    Window& window;
    Vector2 translation;
public:
    const Vector2 &GetTranslation() const;
    void SetTranslation(const Vector2 &translation);
};


#endif //LII_OPENGLRENDERINGPOOL_H
