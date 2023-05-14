//
// Created by Erik on 22/01/24.
//

#ifndef LII_RENDERER_H
#define LII_RENDERER_H
#include "ShapeRenderer.h"
#include "RenderingModel.h"
#include <vector>
#include "RenderMessage.h"
#include "glm.hpp"
#include "EventSource.h"
#include "CoreLifecycleSubscriber.h"
#include <Injector.hpp>
class Core;

class Renderer : public virtual EventSource, public LiiInjector::Injectable, public CoreLifecycleSubscriber
{
public:
    virtual void Render() = 0;
    virtual RenderingModel * CreateModel(SubCommands createCommand) = 0;
    virtual RenderingModel* GetModel(size_t index) = 0;
    virtual void SwapScreenBuffer() = 0;
    virtual std::unique_ptr<ShapeRenderer> AcquireShapeRenderer() = 0;
    virtual void SetViewportSize(int width, int height) = 0;
    virtual void SetViewportSize(const glm::ivec2& size) = 0;
    ~Renderer() override = default;
};


#endif //LII_RENDERER_H
