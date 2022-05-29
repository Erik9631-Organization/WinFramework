//
// Created by Erik on 26/03/22.
//

#include "DefaultMeshMemoryManager.h"
#include "Mesh.h"
#include "Hash.h"
#include "RenderingPriorities.h"
using namespace OpenGL;


DefaultMeshMemoryManager::DefaultMeshMemoryManager(std::unique_ptr<VertexAttributeGroup> properties, const unsigned int &vboSize,
                                                   const unsigned int &eboSize) :
    gpuMemoryManager(properties.get())
{
    vertexAttributes = std::move(properties);
    hash = vertexAttributes->GetHash();
}

void OpenGL::DefaultMeshMemoryManager::Push(Mesh &mesh)
{
    mesh.SetGpuPointer(gpuMemoryManager.Copy<float>((float*)mesh.GetVertices().data(), mesh.GetVertices().size()));
}

const size_t & OpenGL::DefaultMeshMemoryManager::GetHash() const
{
    return hash;
}

void DefaultMeshMemoryManager::Bind()
{
    glBindVertexArray(gpuMemoryManager.GetMemoryStrategy().GetVaoId());
}

void DefaultMeshMemoryManager::UnBind()
{
    glBindVertexArray(0);
}

const unsigned long long int & DefaultMeshMemoryManager::GetId() const
{
    return hash;
}

void DefaultMeshMemoryManager::OnRender(const RenderObjectEventInfo *renderObjectEventInfo)
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
    //GL Draw arrays draws the number of VERTICES!!!!!!.

    unsigned int verticeIndex = gpuPtr.GetMetaData()->GetOffset() / sizeof(float) / vertexAttributes->GetVerticeSize();
    unsigned int numberOfVertices = gpuPtr.GetMetaData()->GetSize() / sizeof(float) / vertexAttributes->GetVerticeSize();
   glDrawArrays(mesh->GetDrawMode(), verticeIndex, numberOfVertices);
}

const int & DefaultMeshMemoryManager::GetPriority()
{
    return RenderingPriorities::Mesh;
}

