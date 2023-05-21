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
#include "RenderingBase.h"
#include <Injector.hpp>
class Core;

class Renderer : public virtual EventSource, public LiiInjector::Injectable, public CoreLifecycleSubscriber, public RenderingBase
{
public:
    virtual void Render() = 0;
    virtual RenderingModel * CreateModel(SubCommands createCommand) = 0;
    virtual RenderingModel* GetModel(size_t index) = 0;
    ~Renderer() override = default;
};


#endif //LII_RENDERER_H
