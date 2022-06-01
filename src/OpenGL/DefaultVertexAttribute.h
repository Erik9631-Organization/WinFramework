//
// Created by Erik on 24/03/22.
//

#ifndef LII_DEFAULTVERTEXATTRIBUTE_H
#define LII_DEFAULTVERTEXATTRIBUTE_H
#include <glew.h>
#include <cstddef>
#include <string>
#include "VertexAttribute.h"

class DefaultVertexAttribute : public VertexAttribute
{
private:
    unsigned int id;
    unsigned int componentCount;
    GLenum type = GL_FLOAT;
    bool normalized = false;
    unsigned int elementSize;
    unsigned int offset;

public:
    DefaultVertexAttribute(const DefaultVertexAttribute& attribute) = default;
    DefaultVertexAttribute(const unsigned int& componentCount, const unsigned int& stride, const unsigned int& offset);
    void SetId(unsigned int id);
    void SetComponentCount(unsigned int componentCount);
    void SetType(GLenum type);
    void SetNormalized(bool normalized);
    void SetElementSize(unsigned int elementSize);
    void SetOffset(unsigned int offset);
    void Create();
    void Enable();
    void Disable();
    unsigned int GetId() const;
    unsigned int GetComponentCount() const;
    GLenum GetType() const;
    bool IsNormalized() const;
    unsigned int GetElementSize() const;
    unsigned int GetOffset() const;

};


#endif //LII_DEFAULTVERTEXATTRIBUTE_H
