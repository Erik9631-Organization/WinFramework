// Created by erik9 on 12/12/2022.
//

#ifndef LII_RENDERINGMODEL_H
#define LII_RENDERINGMODEL_H
#include "RenderingConsumer.h"
#include "Viewport.h"

class Renderer;
class RenderingModel : public RenderingConsumer, public Viewport
{
public:
    virtual float GetZIndex() = 0;
    virtual void Draw() = 0;
    virtual void SetRenderer(Renderer *renderer) = 0;
    virtual void SetModelId(size_t id) = 0;
    virtual void SetVisible(bool visible) = 0;
    virtual bool IsVisible() = 0;
    virtual const size_t & GetModelId() = 0;
    virtual ~RenderingModel() = default;
};


#endif //LII_RENDERINGMODEL_H
