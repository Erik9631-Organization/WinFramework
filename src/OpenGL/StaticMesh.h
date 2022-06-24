//
// Created by Erik on 18/02/22.
//

#ifndef LII_STATICMESH_H
#define LII_STATICMESH_H
#include "Mesh.h"
#include "DefaultGpuMemoryAllocator.h"


namespace OpenGL
{
    class StaticMesh : public Mesh
    {
    public:
        StaticMesh(std::vector<float> vertices, std::vector<unsigned int> indices);
        StaticMesh(std::vector<float> vertices);
        std::vector<float> * SetVertices(std::unique_ptr<std::vector<float>> vertices) override;
        const std::vector<float> * GetVertices() const override;
        ~StaticMesh() override;
        void SetPrimitiveType(const unsigned int &primitiveType) override;
        std::vector<unsigned int> * SetIndexBuffer(std::unique_ptr<std::vector<unsigned int>> indices) override;
        const std::vector<unsigned int> * GetIndices() const override;
        void SetVertices(std::vector<float> vertices) override;
        void SetIndexBufferContent(std::vector<unsigned int> indexOrders) override;
        void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
        const std::string &GetTag() override;
        void SetTag(const std::string &tag) override;
        GpuMemoryAllocator & GetMeshManager() const override;
        const unsigned int & GetPrimitiveType() override;
        const int & GetPriority() override;
        const MemManager::ManagedPtr<float, GpuMemoryStrategy> & GetGpuVerticePointer() override;
        const bool &HasIndices() override;
        const MemManager::ManagedPtr<unsigned int, GpuMemoryStrategy> & GetGpuIndicePointer() override;
        void Load() override;
        void Unload() override;
        const bool &IsLoaded() override;
    private:
        bool loaded = false;
        DefaultGpuMemoryAllocator* manager;
        std::unique_ptr<std::vector<float>> vertices;
        std::unique_ptr<std::vector<unsigned int>> indices;

        MemManager::ManagedPtr<float, GpuMemoryStrategy> gpuVertices;
        MemManager::ManagedPtr<unsigned int, GpuMemoryStrategy> gpuIndices;
        GLenum primitiveType = GL_TRIANGLES;
        std::string tag = "";
    };
}


#endif //LII_STATICMESH_H
