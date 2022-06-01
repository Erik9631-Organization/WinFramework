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

StaticMesh::StaticMesh(std::vector<float> vertices, bool hasIndices)
{
    this->hasIndices = hasIndices;
    this->vertices = std::make_unique<std::vector<float>>(std::move(vertices));
    manager = static_cast<DefaultGpuMemoryAllocator*>(MemoryAllocatorManager::GetMemoryAllocatorManager().Aquire("static"));
    gpuVertices = manager->Push(*this);
    //Delete from the ram as it is no longer needed
    this->vertices.reset();
}

StaticMesh::~StaticMesh()
{
    manager->Erase(gpuVertices);
}


void StaticMesh::SetPrimitiveType(const unsigned int &primitiveType)
{
    this->primitiveType = primitiveType;
}

std::vector<unsigned int> * StaticMesh::SetIndexBuffer(std::unique_ptr<std::vector<unsigned int>> indices)
{
    return nullptr;
}

const std::vector<unsigned int> * StaticMesh::GetIndices() const
{
    return nullptr;
}

void StaticMesh::SetVertices(std::vector<float> vertices)
{
    SetVertices(std::make_unique<std::vector<float>>(std::move(vertices)));
}

void StaticMesh::SetIndexBufferContent(std::vector<unsigned int> indexOrders)
{
    SetIndexBuffer(std::make_unique<std::vector<unsigned int>>(std::move(indexOrders)));
}

void StaticMesh::OnRender(const RenderObjectEventInfo *renderObjectEventInfo)
{
    RenderObjectEventInfo eventInfo{static_cast<Mesh*>(this), nullptr};
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


const MemManager::ManagedPtr<float, GpuMemoryStrategy> & StaticMesh::GetGpuPointer()
{
    return gpuVertices;
}

const bool &StaticMesh::HasIndices()
{
    return hasIndices;
}
