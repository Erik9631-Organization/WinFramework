//
// Created by Erik on 26/03/22.
//

#include "DefaultMeshMemoryManager.h"
#include "Mesh.h"
#include "Hash.h"
#include "RenderingPriorities.h"


using namespace OpenGL;

/**
 * TODO Feature
 * Make the MeshManager react to vertice changes made in the Mesh itself
 */
DefaultMeshMemoryManager::DefaultMeshMemoryManager(std::unique_ptr<VboProperties> properties, const unsigned int &vboSize,
                                                   const unsigned int &eboSize)
{
    this->usage = properties->GetUsage();
    vertexAttributes = std::move(properties);
    hash = vertexAttributes->GetHash();

    glGenVertexArrays(1, &vaoId);
    unsigned int error = glGetError();
    glGenBuffers(1, &vboId);
    error = glGetError();
    glGenBuffers(1, &eboId);
    glBindVertexArray(vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vboSize, NULL, this->usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboSize, NULL, this->usage);
    vertexAttributes->Create();
    vertexAttributes->Enable();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->vboSize = vboSize;
    this->vboExtentionSize = vboSize;

    this->eboSize = eboSize;
    this->eboExtentionSize = eboSize;
}


void OpenGL::DefaultMeshMemoryManager::Push(Mesh &mesh)
{
    unsigned int meshSize = mesh.GetVertices().size() * sizeof(float);

    if(meshSize + vboUsedSize > vboSize)
        ReallocGpuBuffer(vboSize+vboExtentionSize, vboId, GL_ARRAY_BUFFER, vboSize);


    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferSubData(GL_ARRAY_BUFFER, vboUsedSize, meshSize, mesh.GetVertices().data());
    auto vboData = std::make_unique<MeshMetaData>();

    vboData->mesh = &mesh;
    vboData->meshSize = meshSize;
    vboData->meshOffset = vboUsedSize;
    vboData->orderOffset = 0;
    vboData->orderSize = 0;
    vboData->hasEbo = false;

    meshMetaData.try_emplace((size_t)vboData->mesh, std::move(vboData));
    vboUsedSize += meshSize;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void DefaultMeshMemoryManager::ReallocGpuBuffer(const unsigned int &newSize, unsigned int &bufferId,
                                                const GLenum bufferType, unsigned int &bufferSize)
{
    glBindBuffer(GL_COPY_READ_BUFFER, bufferId);
    unsigned int newVboId = 0;
    glGenBuffers(1, &newVboId);
    glBindBuffer(GL_COPY_WRITE_BUFFER, newVboId);
    glBufferData(GL_COPY_WRITE_BUFFER, newSize, 0, this->usage);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, bufferSize);

    glDeleteBuffers(1, &bufferId);

    bufferId = newVboId;
    bufferSize = newSize;

    glBindVertexArray(vaoId);
    glBindBuffer(bufferType, bufferId);
    glBindVertexArray(0);
    glBindBuffer(bufferType, 0);
}
/**
 * TODO Critical
 * Ensure that the mesh doesn't push the same vertices twice.
 * Special condition requries if metaData->hasEbo is already true
 */
void DefaultMeshMemoryManager::PushOrder(const Mesh &mesh)
{
    //If there is no meta data then exit. Can't push vertice order to something that doesn't exist yet
    if(meshMetaData.find((size_t)&mesh) == meshMetaData.end())
        return;

    unsigned int orderSize = mesh.GetVerticeOrders().size() * sizeof(float);
    if(orderSize == 0)
        return;

    if(orderSize + eboUsedSize > orderSize)
        ReallocGpuBuffer(eboSize + eboExtentionSize, eboId, GL_ELEMENT_ARRAY_BUFFER, eboSize);
    glBindVertexArray(vaoId);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, eboUsedSize, orderSize, mesh.GetVerticeOrders().data());
    std::unique_ptr<MeshMetaData>& metaData = meshMetaData.find((size_t)&mesh)->second;
    metaData->orderSize = orderSize;
    metaData->hasEbo = true;
    metaData->orderOffset = eboUsedSize;
    eboUsedSize += orderSize;
}

const size_t & OpenGL::DefaultMeshMemoryManager::GetHash() const
{
    return hash;
}

void DefaultMeshMemoryManager::Bind() const
{
    glBindVertexArray(vaoId);
}

void DefaultMeshMemoryManager::UnBind() const
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
    auto element = meshMetaData.find((size_t)mesh);
    //Nothing to draw as the array contains no data
    if(element == meshMetaData.end())
        return;
    MeshMetaData& data = *element->second;
    if(data.hasEbo == true)
        glDrawElementsBaseVertex(data.mesh->GetDrawMode(), data.orderSize, GL_UNSIGNED_INT, reinterpret_cast<void*>(data.orderOffset), data.meshOffset);
    else
    {
        glDrawArrays(data.mesh->GetDrawMode(), data.meshOffset / vertexAttributes->GetVerticeSize() / sizeof(float), data.meshSize / vertexAttributes->GetVerticeSize() / sizeof(float));
    }
}

const int & DefaultMeshMemoryManager::GetPriority()
{
    return RenderingPriorities::Mesh;
}
