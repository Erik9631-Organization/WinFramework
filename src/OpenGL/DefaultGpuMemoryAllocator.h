//
// Created by Erik on 26/03/22.
//

#ifndef LII_DEFAULTGPUMEMORYALLOCATOR_H
#define LII_DEFAULTGPUMEMORYALLOCATOR_H
#include <vector>
#include <unordered_map>
#include <string>
#include "DefaultVertexAttribute.h"
#include <memory>
#include "GpuMemoryAllocator.h"
#include "VertexAttributeGroup.h"
#include "MemoryManager.hpp"
#include "GpuMemoryStrategy.h"
#include "GpuMemoryStrategySubscriber.h"


class Mesh;
namespace OpenGL
{
    class DefaultGpuMemoryAllocator : public GpuMemoryAllocator, public GpuMemoryStrategySubscriber
    {
    private:
        MemManager::MemoryManager<GpuMemoryStrategy> gpuMemoryManager;
        //After the attributes are created, we only need to keep the hasj
        std::unique_ptr<VertexAttributeGroup> vertexAttributes;
        std::string tag;
        size_t realSize = 0;
    public:
        DefaultGpuMemoryAllocator(std::unique_ptr<VertexAttributeGroup> properties);
        std::pair<MemManager::ManagedPtr<float, GpuMemoryStrategy>, MemManager::ManagedPtr<unsigned int, GpuMemoryStrategy>>
        Push(Mesh &mesh);
        template<typename type>
        void Erase(MemManager::ManagedPtr<type, GpuMemoryStrategy> gpuPtr)
        {
            gpuPtr.Free();
        }
        void Bind() override;
        void UnBind() override;
        const unsigned long long int & GetId() const override;
        void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
        const int & GetPriority() override;
        const std::string &GetTag() override;
        void SetTag(const std::string &tag) override;
        size_t CalculatePadding(const size_t &size, const size_t padding);
        void OnCopyData(MemManager::MetaData &metaData, size_t &usedMemory, const size_t &memoryStartAddr) override;
        void
        OnEraseData(const MemManager::MetaData &metaData, size_t &usedMemory, const size_t &memoryStartAddr) override;
        void OnWriteData(MemManager::MetaData &metaData, size_t &usedMemory, const size_t &memoryStartAddr) override;
    };
}


#endif //LII_DEFAULTGPUMEMORYALLOCATOR_H
