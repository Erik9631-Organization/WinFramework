//
// Created by Erik on 10/04/22.
//

#ifndef LII_RENDEROBJECT_H
#define LII_RENDEROBJECT_H
#include <memory>
#include "RenderObjectEventInfo.h"
#include "RenderObjectSubscriber.h"
#include "RenderObjectSubject.h"

namespace OpenGL
{
    class RenderObject : public RenderObjectSubscriber, public RenderObjectSubject
    {
    public:
        ~RenderObject() = default;
    };
}


#endif //LII_RENDEROBJECT_H
