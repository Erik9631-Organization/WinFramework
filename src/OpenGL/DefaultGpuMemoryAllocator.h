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


class Mesh;
namespace OpenGL
{
    class DefaultGpuMemoryAllocator : public GpuMemoryAllocator
    {
    private:
        MemManager::MemoryManager<GpuMemoryStrategy> gpuMemoryManager;
        //After the attributes are created, we only need to keep the hasj
        std::unique_ptr<VertexAttributeGroup> vertexAttributes;
        std::string tag;
    public:
        DefaultGpuMemoryAllocator(std::unique_ptr<VertexAttributeGroup> properties);
        MemManager::ManagedPtr<float, GpuMemoryStrategy> Push(Mesh &mesh);
        void Erase(MemManager::ManagedPtr<float, GpuMemoryStrategy> gpuPtr);
        void Bind() override;
        void UnBind() override;
        const unsigned long long int & GetId() const override;
        void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
        const int & GetPriority() override;
        const std::string &GetTag() override;
        void SetTag(const std::string &tag) override;
    };
}


#endif //LII_DEFAULTGPUMEMORYALLOCATOR_H
