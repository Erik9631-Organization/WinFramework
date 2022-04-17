//
// Created by Erik on 24/03/22.
//

#include "FloatVertexAttribute.h"
#include "Hash.h"
using namespace std;


/**
 * TODO
 * The attribute should become unchangable after it was created. Also hash should be calculated on creation. It won't change afterwards
*/
FloatVertexAttribute::FloatVertexAttribute(const unsigned int &componentCount, const unsigned int &elementSize, const unsigned int& offset)
{
    SetComponentCount(componentCount);
    SetElementSize(elementSize);
    SetOffset(offset);
}

unsigned int FloatVertexAttribute::GetId() const
{
    return id;
}

void FloatVertexAttribute::SetId(unsigned int id)
{
    FloatVertexAttribute::id = id;
}

unsigned int FloatVertexAttribute::GetComponentCount() const
{
    return componentCount;
}

void FloatVertexAttribute::SetComponentCount(unsigned int componentCount)
{
    FloatVertexAttribute::componentCount = componentCount;
    SetStrComponentCount(componentCount);
}

GLenum FloatVertexAttribute::GetType() const
{
    return type;
}

void FloatVertexAttribute::SetType(GLenum type)
{
    FloatVertexAttribute::type = type;
    SetStrType(type);
}

bool FloatVertexAttribute::IsNormalized() const
{
    return normalized;
}

void FloatVertexAttribute::SetNormalized(bool normalized)
{
    FloatVertexAttribute::normalized = normalized;
    SetStrNormalized(normalized);
}

unsigned int FloatVertexAttribute::GetElementSize() const
{
    return elementSize;
}

void FloatVertexAttribute::SetElementSize(unsigned int elementSize)
{
    FloatVertexAttribute::elementSize = elementSize;
    SetStrElementSize(elementSize);
}

unsigned int FloatVertexAttribute::GetOffset() const
{
    return offset;
}

void FloatVertexAttribute::SetOffset(unsigned int offset)
{
    FloatVertexAttribute::offset = offset;
    SetStrOffset(offset);
}

void FloatVertexAttribute::Create()
{
    glVertexAttribPointer(id, componentCount, type, normalized, sizeof(float) * elementSize, (void*) (offset * sizeof(float)));
}

void FloatVertexAttribute::Enable()
{
    glEnableVertexAttribArray(id);
}

void FloatVertexAttribute::Disable()
{
    glDisableVertexAttribArray(id);
}

void FloatVertexAttribute::SetStrComponentCount(const unsigned int &strComponentCount)
{
   this->strComponentCount = "componentCount:"+ to_string(strComponentCount);
}

void FloatVertexAttribute::SetStrType(const unsigned int &strType)
{
    this->strType = "type:"+to_string(strType);
}

void FloatVertexAttribute::SetStrNormalized(const bool &strNormalized)
{
    this->strNormalized = "normalized:"+to_string(strNormalized);
}

void FloatVertexAttribute::SetStrElementSize(const unsigned int &strElementSize)
{
    this->strElementSize = "elementSize"+to_string(strElementSize);
}

void FloatVertexAttribute::SetStrOffset(const unsigned int &strOffset)
{
    this->strOffset = "offset"+to_string(strOffset);
}

const size_t & FloatVertexAttribute::GetHash() const
{
    std::string hash = strComponentCount + ";" + strType + ";" + strNormalized + ";" + strElementSize + ";" + strOffset + ";";
    return Utils::HashDjb2::CalculateHash(hash);
}