//
// Created by Erik on 29/03/22.
//

#ifndef LII_VERTEXATTRIBUTE_H
#define LII_VERTEXATTRIBUTE_H
#include "Hashable.h"

class VertexAttribute
{
public:
    virtual void SetId(unsigned int id) = 0;
    virtual void SetComponentCount(unsigned int componentCount) = 0;
    virtual void SetType(GLenum type) = 0;
    virtual void SetNormalized(bool normalized) = 0;
    virtual void SetElementSize(unsigned int elementSize) = 0;
    virtual void SetOffset(unsigned int offset) = 0;
    virtual void Create() = 0;
    virtual void Enable() = 0;
    virtual void Disable() = 0;
    virtual unsigned int GetId() const = 0;
    virtual unsigned int GetComponentCount() const = 0;
    virtual unsigned int GetType() const = 0;
    virtual bool IsNormalized() const = 0;
    virtual unsigned int GetElementSize() const = 0;
    virtual unsigned int GetOffset() const = 0;
    virtual ~VertexAttribute() = default;
};


#endif //LII_VERTEXATTRIBUTE_H
