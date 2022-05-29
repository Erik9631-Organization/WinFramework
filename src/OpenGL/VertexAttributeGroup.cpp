//
// Created by Erik on 29/03/22.
//

#include "VertexAttributeGroup.h"

const size_t & VertexAttributeGroup::GetHash() const
{
    return hash;
}

void VertexAttributeGroup::Create()
{
    for(auto& i : vertexAttributes)
        i.second->Create();
}

void VertexAttributeGroup::Enable()
{
    for(auto& i : vertexAttributes)
        i.second->Enable();
}

void VertexAttributeGroup::Disable()
{
    for(auto& i : vertexAttributes)
        i.second->Disable();
}

const GLenum &VertexAttributeGroup::GetUsage() const
{
    return usage;
}

VertexAttributeGroup::VertexAttributeGroup(std::vector<std::unique_ptr<VertexAttribute>> &attributes, GLenum usage)
{
    std::string stringHash = "usage:"+std::to_string(usage)+";";
    this->usage = usage;
    unsigned int counter = 0;
    for(std::unique_ptr<VertexAttribute>& attribute : attributes)
    {
        attribute->SetId(counter);
        stringHash += std::to_string(attribute->GetHash()) + ";";
        verticeSize += attribute->GetComponentCount();
        vertexAttributes.try_emplace(attribute->GetHash(), std::move(attribute));
        counter++;
    }
    hash = Utils::HashDjb2::CalculateHash(stringHash);
}

unsigned int VertexAttributeGroup::GetVerticeSize()
{
    return verticeSize;
}

unsigned int VertexAttributeGroup::GetSize()
{
    return vertexAttributes.size();
}
