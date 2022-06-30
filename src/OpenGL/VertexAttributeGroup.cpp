//
// Created by Erik on 29/03/22.
//

#include "VertexAttributeGroup.h"

void VertexAttributeGroup::Create()
{
    for(auto& i : vertexAttributes)
        i->Create();
}

void VertexAttributeGroup::Enable()
{
    for(auto& i : vertexAttributes)
        i->Enable();
}

void VertexAttributeGroup::Disable()
{
    for(auto& i : vertexAttributes)
        i->Disable();
}


VertexAttributeGroup::VertexAttributeGroup(std::vector<std::unique_ptr<VertexAttribute>> &attributes)
{
    for(std::unique_ptr<VertexAttribute>& attribute : attributes)
    {
        attribute->SetId(lastId);
        verticeSize += attribute->GetComponentCount();
        vertexAttributes.push_back(std::move(attribute));
        lastId++;
    }
}

const unsigned int & VertexAttributeGroup::GetVerticeCount()
{
    return verticeSize;
}

const std::vector<std::unique_ptr<VertexAttribute>> & VertexAttributeGroup::GetVertexAttributes() const
{
    return vertexAttributes;
}

void VertexAttributeGroup::AddVertexAttribute(std::unique_ptr<VertexAttribute> vertexAttribute)
{
    verticeSize += vertexAttribute->GetComponentCount();
    vertexAttribute->SetId(lastId);
    vertexAttributes.push_back(std::move(vertexAttribute));
    lastId++;
}

void VertexAttributeGroup::RemoveVertexAttribute(const std::vector<std::unique_ptr<VertexAttribute>>::iterator &iterator)
{
    vertexAttributes.erase(iterator);
}

