// Created by erik9 on 12/12/2022.
//

#ifndef LII_RENDERINGMODEL_H
#define LII_RENDERINGMODEL_H
#include "Renderer.h"

class RenderingModel
{
public:
    virtual void Redraw() = 0;
    virtual void SetRenderer(Renderer* renderer) = 0;
    virtual ~RenderingModel() = default;
};


#endif //LII_RENDERINGMODEL_H
