//
// Created by Erik on 26/03/22.
//

#ifndef LII_DEFAULTMESHMEMORYMANAGER_H
#define LII_DEFAULTMESHMEMORYMANAGER_H
#include <vector>
#include <unordered_map>
#include <string>
#include "FloatVertexAttribute.h"
#include <memory>
#include "MeshMemoryManager.h"
#include "VertexAttributeGroup.h"
#include "MemoryManager.hpp"
#include "GpuMemoryStrategy.h"


class Mesh;
namespace OpenGL
{
    class DefaultMeshMemoryManager : public MeshMemoryManager
    {
    private:
        MemManager::MemoryManager<GpuMemoryStrategy> gpuMemoryManager;
        //After the attributes are created, we only need to keep the hasj
        size_t hash;
        std::unique_ptr<VertexAttributeGroup> vertexAttributes;
    public:
        DefaultMeshMemoryManager(std::unique_ptr<VertexAttributeGroup> properties, const unsigned int &vboSize,
                                 const unsigned int &eboSize);
        void Push(Mesh &mesh);
        const size_t & GetHash() const override;
        void Bind() override;
        void UnBind() override;
        const unsigned long long int & GetId() const override;
        void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
        const int & GetPriority() override;
    };
}


#endif //LII_DEFAULTMESHMEMORYMANAGER_H
