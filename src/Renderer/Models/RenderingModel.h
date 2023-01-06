// Created by erik9 on 12/12/2022.
//

#ifndef LII_RENDERINGMODEL_H
#define LII_RENDERINGMODEL_H
#include "RenderingConsumer.h"

class RenderingProvider;
class RenderingModel : public RenderingConsumer
{
public:
    virtual void Redraw() = 0;
    virtual void SetRenderingProvider(RenderingProvider *renderer) = 0;
    virtual void SetAssociatedModelId(unsigned long long id) = 0;
    virtual long long int & GetModelId() = 0;
    virtual ~RenderingModel() = default;
};


#endif //LII_RENDERINGMODEL_H
