//
// Created by Erik on 18/02/22.
//

#include "StaticMesh.h"
#include "MemoryAllocatorManager.h"
#include "RenderingPriorities.h"

using namespace OpenGL;

std::vector<float> * StaticMesh::SetVertices(std::unique_ptr<std::vector<float>> vertices)
{
    this->vertices = std::move(vertices);
    return this->vertices.get();
}

const std::vector<float> * StaticMesh::GetVertices() const
{
    return vertices.get();
}

StaticMesh::StaticMesh(std::vector<float> vertices, std::vector<unsigned int> indices)
{
    this->vertices = std::make_unique<std::vector<float>>(std::move(vertices));
    if(indices.size() != 0)
        this->indices = std::make_unique<std::vector<unsigned int>>(std::move(indices));

    manager = static_cast<DefaultGpuMemoryAllocator*>(MemoryAllocatorManager::GetMemoryAllocatorManager().Aquire("static"));
    auto pointerPair = manager->Push(*this);
    gpuVertices = pointerPair.first;
    gpuIndices = pointerPair.second;

    //Delete from the system RAM as it is no longer needed
    this->vertices.reset();
    this->indices.reset();
    loaded = true;
}

StaticMesh::~StaticMesh()
{
    Unload();
}


void StaticMesh::SetPrimitiveType(const unsigned int &primitiveType)
{
    this->primitiveType = primitiveType;
}

std::vector<unsigned int> * StaticMesh::SetIndexBuffer(std::unique_ptr<std::vector<unsigned int>> indices)
{
    //Static mesh can not be set
    return nullptr;
}

const std::vector<unsigned int> * StaticMesh::GetIndices() const
{
    //Static mesh can not be get
    return indices.get();
}

void StaticMesh::SetVertices(std::vector<float> vertices)
{
    //Static mesh can not be set
}

void StaticMesh::SetIndexBufferContent(std::vector<unsigned int> indexOrders)
{
    //Static mesh can not be set
}

void StaticMesh::OnRender(const RenderObjectEventInfo *renderObjectEventInfo)
{
    RenderObjectEventInfo eventInfo{static_cast<Mesh*>(this)};
    manager->OnRender(&eventInfo);
}

const std::string &StaticMesh::GetTag()
{
    return tag;
}

void OpenGL::StaticMesh::SetTag(const std::string &tag)
{
    this->tag = tag;
}

OpenGL::GpuMemoryAllocator & StaticMesh::GetMeshManager() const
{
    return *manager;
}

const unsigned int & StaticMesh::GetPrimitiveType()
{
    return primitiveType;
}

const int & StaticMesh::GetPriority()
{
    return RenderingPriorities::Mesh;
}

const MemManager::ManagedPtr<float, GpuMemoryStrategy> & StaticMesh::GetGpuVerticePointer()
{
    return gpuVertices;
}

const bool &StaticMesh::HasIndices()
{
    if(gpuIndices.GetMetaData() == nullptr)
        return false;
    return true;
}

const MemManager::ManagedPtr<unsigned int, GpuMemoryStrategy> & StaticMesh::GetGpuIndicePointer()
{
    return gpuIndices;
}

StaticMesh::StaticMesh(std::vector<float> vertices) : StaticMesh(std::move(vertices), {})
{

}

void StaticMesh::Load()
{
    //Static mesh is loaded on creation, no implementation needed
}

void StaticMesh::Unload()
{
    manager->Erase(gpuVertices);
    if(gpuIndices.GetMetaData() != nullptr)
        manager->Erase(gpuIndices);
    loaded = false;
}

const bool &StaticMesh::IsLoaded()
{
    return loaded;
}
