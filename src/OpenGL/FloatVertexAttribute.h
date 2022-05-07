//
// Created by Erik on 24/03/22.
//

#ifndef LII_FLOATVERTEXATTRIBUTE_H
#define LII_FLOATVERTEXATTRIBUTE_H
#include <glew.h>
#include <cstddef>
#include <string>
#include "VertexAttribute.h"

class FloatVertexAttribute : public VertexAttribute
{
private:
    unsigned int id;
    unsigned int componentCount;
    GLenum type = GL_FLOAT;
    bool normalized = false;
    unsigned int elementSize;
    unsigned int offset;

    //For hash
    std::string strComponentCount;
    std::string strType;
    std::string strNormalized;
    std::string strElementSize;
    std::string strOffset;

    void SetStrComponentCount(const unsigned int &strComponentCount);
    void SetStrType(const unsigned int &strType);
    void SetStrNormalized(const bool &strNormalized);
    void SetStrElementSize(const unsigned int &strElementSize);
    void SetStrOffset(const unsigned int &strOffset);

public:
    FloatVertexAttribute(const FloatVertexAttribute& attribute) = default;
    FloatVertexAttribute(const unsigned int& componentCount, const unsigned int& stride, const unsigned int& offset);
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
    const size_t & GetHash() const override;

};


#endif //LII_FLOATVERTEXATTRIBUTE_H
