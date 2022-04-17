//
// Created by Erik on 27/03/22.
//

#ifndef LII_MESHMEMORYMANAGER_H
#define LII_MESHMEMORYMANAGER_H

#include "Hashable.h"
#include "Identifiable.h"
#include "RenderObjectSubscriber.h"
class Mesh;

namespace OpenGL
{

    class MeshMemoryManager : public Hashable, public Identifiable, public RenderObjectSubscriber
    {
    public:
        virtual void Push(Mesh &mesh) = 0;
        virtual void PushOrder(const Mesh &mesh) = 0;
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
    };
}


#endif //LII_MESHMEMORYMANAGER_H
