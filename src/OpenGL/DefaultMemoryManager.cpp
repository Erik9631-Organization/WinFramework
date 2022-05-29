//
// Created by Erik on 27/03/22.
//

#include "DefaultMemoryManager.h"
#include "DefaultMeshMemoryManager.h"

OpenGL::MeshMemoryManager &
OpenGL::DefaultMemoryManager::Aquire(const unsigned int &usage, std::unique_ptr<VertexAttributeGroup> attributes)
{
    //First try to find by hash
    auto element = memoryMap.find(attributes->GetHash());
    if(element != memoryMap.end())
        return *element->second;
    //Otherwise try to create a new one
    std::unique_ptr<DefaultMeshMemoryManager> vector = std::make_unique<DefaultMeshMemoryManager>(std::move(attributes), 10000, 10000);
    DefaultMeshMemoryManager& managerReference = *vector;

    memoryMap.try_emplace(managerReference.GetHash(), std::move(vector));
    return managerReference;
}

std::unique_ptr<OpenGL::MeshMemoryManager> &OpenGL::DefaultMemoryManager::Aquire(const long long int &id)
{
    return uniqueNullPtr;
}
