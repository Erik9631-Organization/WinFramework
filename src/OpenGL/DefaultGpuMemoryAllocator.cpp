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

MemManager::ManagedPtr<float, GpuMemoryStrategy> OpenGL::DefaultGpuMemoryAllocator::Push(Mesh &mesh)
{
    return gpuMemoryManager.Copy<float>((float*)mesh.GetVertices()->data(), mesh.GetVertices()->size());
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
    auto& gpuPtr = mesh->GetGpuPointer();

//    //auto element = meshMetaData.find((size_t)mesh);
//    //Nothing to draw as the array contains no data
//    if(element == meshMetaData.end())
//        return;
//    MeshMetaData& data = *element->second;
    //if(data.hasEbo == true)
    //    glDrawElementsBaseVertex(data.mesh->GetDrawMode(), data.orderSize, GL_UNSIGNED_INT, reinterpret_cast<void*>(data.orderOffset), data.meshOffset);
    //else
    //GL Draw arrays draws the number of VERTICES!!!!!!

    unsigned int verticeIndex = gpuPtr.GetMetaData()->GetOffset() / sizeof(float) / vertexAttributes->GetVerticeSize();
    unsigned int numberOfVertices = gpuPtr.GetMetaData()->GetSize() / sizeof(float) / vertexAttributes->GetVerticeSize();
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

void DefaultGpuMemoryAllocator::Erase(MemManager::ManagedPtr<float, GpuMemoryStrategy> gpuPtr)
{
    gpuPtr.Free();
}

