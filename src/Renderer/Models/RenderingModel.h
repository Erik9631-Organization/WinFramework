// Created by erik9 on 12/12/2022.
//

#ifndef LII_RENDERINGMODEL_H
#define LII_RENDERINGMODEL_H
#include "RenderingConsumer.h"

class Renderer;
class RenderingModel : public RenderingConsumer
{
public:
    virtual float GetZIndex() = 0;
    virtual void Draw() = 0;
    virtual void SetRenderer(Renderer *renderer) = 0;
    virtual void SetModelId(unsigned long long id) = 0;
    virtual size_t & GetModelId() = 0;
    virtual ~RenderingModel() = default;
};


#endif //LII_RENDERINGMODEL_H
