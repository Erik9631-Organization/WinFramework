//
// Created by Erik on 26/03/22.
//

#include "DefaultGpuMemoryAllocator.h"
#include "Mesh.h"
#include "Hash.h"
#include "RenderingPriorities.h"
using namespace OpenGL;


DefaultGpuMemoryAllocator::DefaultGpuMemoryAllocator(std::unique_ptr<VertexAttributeGroup> properties) :
    gpuMemoryManager(properties.get())
{
    vertexAttributes = std::move(properties);
}

std::pair<MemManager::ManagedPtr<float, GpuMemoryStrategy>, MemManager::ManagedPtr<unsigned int, GpuMemoryStrategy>>
OpenGL::DefaultGpuMemoryAllocator::Push(Mesh &mesh)
{
    std::pair<MemManager::ManagedPtr<float, GpuMemoryStrategy>, MemManager::ManagedPtr<unsigned int, GpuMemoryStrategy>> pointerPair;

    pointerPair.first = gpuMemoryManager.Copy<float>((float*)mesh.GetVertices()->data(), mesh.GetVertices()->size());
    if(mesh.GetIndices() == nullptr)
        return pointerPair;

    pointerPair.second = gpuMemoryManager.Copy<unsigned int>((unsigned int*)mesh.GetIndices()->data(), mesh.GetIndices()->size());
    return pointerPair;
}

void DefaultGpuMemoryAllocator::Bind()
{
    glBindVertexArray(gpuMemoryManager.GetMemoryStrategy().GetVaoId());
}

void DefaultGpuMemoryAllocator::UnBind()
{
    glBindVertexArray(0);
}


void DefaultGpuMemoryAllocator::OnRender(const RenderObjectEventInfo *renderObjectEventInfo)
{
    Mesh* mesh = renderObjectEventInfo->GetSrc<Mesh>();
    auto& verticePtr = mesh->GetGpuVerticePointer();
    auto& indicePtr = mesh->GetGpuIndicePointer();

//    //auto element = meshMetaData.find((size_t)mesh);
//    //Nothing to draw as the array contains no data
//    if(element == meshMetaData.end())
//        return;
//    MeshMetaData& data = *element->second;
    //if(data.hasEbo == true)
    //    glDrawElementsBaseVertex(data.mesh->GetDrawMode(), data.orderSize, GL_UNSIGNED_INT, reinterpret_cast<void*>(data.orderOffset), data.meshOffset);
    //else
    //GL Draw arrays draws the number of VERTICES!!!!!!

    unsigned int verticeIndex = verticePtr.GetMetaData()->GetOffset() / sizeof(float) / vertexAttributes->GetVerticeSize();
    unsigned int numberOfVertices = verticePtr.GetMetaData()->GetSize() / sizeof(float) / vertexAttributes->GetVerticeSize();

    if(indicePtr.GetMetaData() != nullptr)
    {
        glDrawElementsBaseVertex(mesh->GetPrimitiveType(), indicePtr.GetMetaData()->GetSize() / sizeof(unsigned int),
                       GL_UNSIGNED_INT, (void*)indicePtr.GetMetaData()->GetOffset(), verticeIndex);
        return;
    }


    glDrawArrays(mesh->GetPrimitiveType(), verticeIndex, numberOfVertices);
}

const int & DefaultGpuMemoryAllocator::GetPriority()
{
    return RenderingPriorities::Mesh;
}

const std::string &DefaultGpuMemoryAllocator::GetTag()
{
    return tag;
}

void DefaultGpuMemoryAllocator::SetTag(const std::string &tag)
{
    this->tag = tag;
}

const unsigned long long int &DefaultGpuMemoryAllocator::GetId() const
{
    return gpuMemoryManager.GetStartAddr();
}

