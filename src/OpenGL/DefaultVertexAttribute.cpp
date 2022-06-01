//
// Created by Erik on 24/03/22.
//

#include "DefaultVertexAttribute.h"
#include "Hash.h"
using namespace std;


DefaultVertexAttribute::DefaultVertexAttribute(const unsigned int &componentCount, const unsigned int &stride, const unsigned int& offset)
{
    SetComponentCount(componentCount);
    SetElementSize(stride);
    SetOffset(offset);
}

unsigned int DefaultVertexAttribute::GetId() const
{
    return id;
}

void DefaultVertexAttribute::SetId(unsigned int id)
{
    DefaultVertexAttribute::id = id;
}

unsigned int DefaultVertexAttribute::GetComponentCount() const
{
    return componentCount;
}

void DefaultVertexAttribute::SetComponentCount(unsigned int componentCount)
{
    DefaultVertexAttribute::componentCount = componentCount;
}

GLenum DefaultVertexAttribute::GetType() const
{
    return type;
}

void DefaultVertexAttribute::SetType(GLenum type)
{
    DefaultVertexAttribute::type = type;
}

bool DefaultVertexAttribute::IsNormalized() const
{
    return normalized;
}

void DefaultVertexAttribute::SetNormalized(bool normalized)
{
    DefaultVertexAttribute::normalized = normalized;
}

unsigned int DefaultVertexAttribute::GetElementSize() const
{
    return elementSize;
}

void DefaultVertexAttribute::SetElementSize(unsigned int elementSize)
{
    DefaultVertexAttribute::elementSize = elementSize;
}

unsigned int DefaultVertexAttribute::GetOffset() const
{
    return offset;
}

void DefaultVertexAttribute::SetOffset(unsigned int offset)
{
    DefaultVertexAttribute::offset = offset;
}

void DefaultVertexAttribute::Create()
{
    glVertexAttribPointer(id, componentCount, type, normalized, sizeof(float) * elementSize, (void*) (offset * sizeof(float)));
}

void DefaultVertexAttribute::Enable()
{
    glEnableVertexAttribArray(id);
}

void DefaultVertexAttribute::Disable()
{
    glDisableVertexAttribArray(id);
}