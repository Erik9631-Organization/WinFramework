//
// Created by Erik on 27/03/22.
//

#ifndef LII_MEMORYALLOCATORMANAGER_H
#define LII_MEMORYALLOCATORMANAGER_H
#include "DefaultVertexAttribute.h"
#include "GpuMemoryAllocator.h"
#include "VertexAttributeGroup.h"
#include <unordered_map>

namespace OpenGL
{
    class MemoryAllocatorManager
    {
    public:
        MemoryAllocatorManager();
        GpuMemoryAllocator * Aquire(const std::string &allocatorTag);
        GpuMemoryAllocator * AddAllocator(std::unique_ptr<GpuMemoryAllocator> allocator);
        void RemoveAllocator(const std::string& allocatorTag);
        template<typename type, typename ... Args>
        GpuMemoryAllocator* Create(const std::string& tag, Args ... args)
        {
            GpuMemoryAllocator* allocator = new type(args...);
            auto allocatorPtr = std::unique_ptr<GpuMemoryAllocator>(allocator);
            auto iterator = memoryMap.try_emplace(allocatorPtr->GetTag(), std::move(allocator));
            if(iterator.second == false)
                return nullptr;
            return allocator;
        }
        static MemoryAllocatorManager& GetMemoryAllocatorManager();
    private:
        std::unique_ptr<GpuMemoryAllocator> uniqueNullPtr;
        std::unordered_map<std::string, std::unique_ptr<GpuMemoryAllocator>> memoryMap;
        static MemoryAllocatorManager* manager;
    };
}


#endif //LII_MEMORYALLOCATORMANAGER_H
