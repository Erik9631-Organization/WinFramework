//
// Created by Erik on 19/02/22.
//

#ifndef LII_OPENGLRENDERERPOOL_H
#define LII_OPENGLRENDERERPOOL_H
#include <unordered_map>
#include <memory>
class OpenGLRenderer;
class Renderable;

class OpenGLRendererPool
{
public:
    static OpenGLRendererPool& GetRenderPool();
    OpenGLRenderer &AquireRenderer(const Renderable &renderable);
private:
    OpenGLRendererPool() = default;
    OpenGLRendererPool(OpenGLRendererPool &&) = default;
    OpenGLRendererPool(OpenGLRendererPool &) = default;
    static OpenGLRendererPool* rendererPool;
    std::unordered_map<const Renderable*, std::unique_ptr<OpenGLRenderer>> renderers;
};


#endif //LII_OPENGLRENDERERPOOL_H
