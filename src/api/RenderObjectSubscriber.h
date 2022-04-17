//
// Created by Erik on 20/03/22.
//

#ifndef LII_RENDEROBJECTSUBSCRIBER_H
#define LII_RENDEROBJECTSUBSCRIBER_H
#include "RenderObjectEventInfo.h"
#include <memory>

class RenderObjectSubscriber
{
public:
    virtual void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) = 0;
    virtual const int & GetPriority() = 0;
    ~RenderObjectSubscriber() = default;
};

#endif //LII_RENDEROBJECTSUBSCRIBER_H
