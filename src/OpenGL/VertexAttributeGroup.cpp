//
// Created by Erik on 29/03/22.
//

#include "VboProperties.h"

const size_t & VboProperties::GetHash() const
{
    return hash;
}

void VboProperties::Create()
{
    for(auto& i : vertexAttributes)
        i.second->Create();
}

void VboProperties::Enable()
{
    for(auto& i : vertexAttributes)
        i.second->Enable();
}

void VboProperties::Disable()
{
    for(auto& i : vertexAttributes)
        i.second->Disable();
}

const GLenum &VboProperties::GetUsage() const
{
    return usage;
}

VboProperties::VboProperties(std::vector<std::unique_ptr<VertexAttribute>> &attributes, GLenum usage)
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

unsigned int VboProperties::GetVerticeSize()
{
    return verticeSize;
}
