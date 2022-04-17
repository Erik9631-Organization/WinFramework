//
// Created by Erik on 10/04/22.
//

#ifndef LII_RENDEROBJECT_H
#define LII_RENDEROBJECT_H
#include <memory>
#include "RenderObjectEventInfo.h"
#include "RenderObjectSubscriber.h"

namespace OpenGL
{
    class RenderObject : public RenderObjectSubscriber
    {
    public:
        virtual void AddRenderObjectSubscriber(RenderObjectSubscriber& subscriber) = 0;
        virtual void RemoveRenderObjectSubscriber(const RenderObjectSubscriber& subscriber) = 0;
        virtual void NotifyOnRenderObjects(const RenderObjectEventInfo &eventInfo) = 0;
        ~RenderObject() = default;
    };
}


#endif //LII_RENDEROBJECT_H
