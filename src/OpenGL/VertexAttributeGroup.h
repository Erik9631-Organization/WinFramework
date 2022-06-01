//
// Created by Erik on 29/03/22.
//

#ifndef LII_VERTEXATTRIBUTEGROUP_H
#define LII_VERTEXATTRIBUTEGROUP_H

#include <glew.h>
#include "VertexAttribute.h"
#include <vector>
#include <map>
#include "Hash.h"
#include "DefaultVertexAttribute.h"
#include <memory>

class VertexAttributeGroup
{
private:
    std::vector<std::unique_ptr<VertexAttribute>> vertexAttributes;
    unsigned int verticeSize = 0;

public:
    VertexAttributeGroup(std::vector<std::unique_ptr<VertexAttribute>> &attributes);
    VertexAttributeGroup() = default;
    void AddVertexAttribute(std::unique_ptr<VertexAttribute> vertexAttribute);
    void RemoveVertexAttribute(const std::vector<std::unique_ptr<VertexAttribute>>::iterator &iterator);
    void Create();
    void Enable();
    void Disable();
    const unsigned int & GetVerticeSize();
    const std::vector<std::unique_ptr<VertexAttribute>> & GetVertexAttributes() const;
    unsigned int lastId = 0;

};


#endif //LII_VERTEXATTRIBUTEGROUP_H
