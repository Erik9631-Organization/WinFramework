//
// Created by Erik on 27/03/22.
//

#include "MemoryAllocatorManager.h"
#include "DefaultGpuMemoryAllocator.h"
using namespace OpenGL;

MemoryAllocatorManager* MemoryAllocatorManager::manager = new MemoryAllocatorManager();

GpuMemoryAllocator * OpenGL::MemoryAllocatorManager::AddAllocator(std::unique_ptr<GpuMemoryAllocator> allocator)
{
    if( memoryMap.find(allocator->GetTag()) == memoryMap.end() )
        return nullptr;
    auto iterator = memoryMap.try_emplace(allocator->GetTag(), std::move(allocator));
    if(!iterator.second)
        return nullptr;

    return iterator.first->second.get();

}

GpuMemoryAllocator * OpenGL::MemoryAllocatorManager::Aquire(const std::string &allocatorTag)
{
    auto foundAllocator = memoryMap.find(allocatorTag);
    if(foundAllocator == memoryMap.end())
        return nullptr;
    return foundAllocator->second.get();
}

MemoryAllocatorManager::MemoryAllocatorManager()
{
    std::unique_ptr<VertexAttributeGroup> defaultVertexAttributes = std::make_unique<VertexAttributeGroup>();
    //Vertex
    defaultVertexAttributes->AddVertexAttribute(std::make_unique<DefaultVertexAttribute>(3, 8, 0));
    //Texture
    defaultVertexAttributes->AddVertexAttribute(std::make_unique<DefaultVertexAttribute>(2, 8, 3));
    //Normal
    defaultVertexAttributes->AddVertexAttribute(std::make_unique<DefaultVertexAttribute>(3, 8, 5));
    //Create default allocator
    std::unique_ptr<GpuMemoryAllocator> allocator = std::make_unique<DefaultGpuMemoryAllocator>(std::move(defaultVertexAttributes));
    allocator->SetTag("static");
    memoryMap.try_emplace(allocator->GetTag(), std::move(allocator));
}

MemoryAllocatorManager &MemoryAllocatorManager::GetMemoryAllocatorManager()
{
    return *manager;
}

void MemoryAllocatorManager::RemoveAllocator(const std::string& allocatorTag)
{
    auto foundAllocator = memoryMap.find(allocatorTag);
    if(foundAllocator != memoryMap.end())
        memoryMap.erase(foundAllocator);
}
