//
// Created by Erik on 29/06/22.
//

#ifndef LII_RENDEROBJECTSUBJECT_H
#define LII_RENDEROBJECTSUBJECT_H
#include "RenderObjectSubscriber.h"

namespace OpenGL
{
    class RenderObjectSubject
    {
    public:
        virtual void AddRenderObjectSubscriber(RenderObjectSubscriber& subscriber) = 0;
        virtual void RemoveRenderObjectSubscriber(const RenderObjectSubscriber& subscriber) = 0;
        virtual void NotifyOnRenderObjects(const RenderObjectEventInfo &eventInfo) = 0;
    };

}

#endif //LII_RENDEROBJECTSUBJECT_H
