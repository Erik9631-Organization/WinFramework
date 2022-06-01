//
// Created by Erik on 27/03/22.
//

#ifndef LII_GPUMEMORYALLOCATOR_H
#define LII_GPUMEMORYALLOCATOR_H

#include "Hashable.h"
#include "Identifiable.h"
#include "RenderObjectSubscriber.h"
#include "Taggable.h"
#include "ManagedPtr.hpp"

class Mesh;

namespace OpenGL
{

    class GpuMemoryAllocator : public Identifiable, public RenderObjectSubscriber, public Taggable
    {
    public:
        virtual void Bind() = 0;
        virtual void UnBind() = 0;
    };
}


#endif //LII_GPUMEMORYALLOCATOR_H
