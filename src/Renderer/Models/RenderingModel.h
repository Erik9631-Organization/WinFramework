// Created by erik9 on 12/12/2022.
//

#ifndef LII_RENDERINGMODEL_H
#define LII_RENDERINGMODEL_H
#include "RenderingProvider.h"

class RenderingModel
{
public:
    virtual void Redraw() = 0;
    virtual void SetRenderingProvider(RenderingProvider *renderer) = 0;
    virtual ~RenderingModel() = default;
};


#endif //LII_RENDERINGMODEL_H
