//
// Created by Erik on 18/02/22.
//

#include "DefaultMesh.h"
#include <glew.h>
#include <wglew.h>
#include "RenderEventInfo.h"
#include "MemoryManager.h"
#include "RenderingPriorities.h"

using namespace OpenGL;

std::vector<float> &DefaultMesh::SetVertices(std::unique_ptr<std::vector<float>> vertices)
{
    this->vertices = std::move(vertices);
    return *this->vertices;
}

const std::vector<float> &DefaultMesh::GetVertices() const
{
    return *vertices;
}

int OpenGL::DefaultMesh::GetComponentCount()
{
    return componentCount;
}

DefaultMesh::DefaultMesh(int componentCount, const std::vector<FloatVertexAttribute>& attributes) :
    OpenGL::DefaultMesh(componentCount, {}, defaultAttributes)
{
    this->componentCount = componentCount;
}
/**
 * TODO
 * Create a memory manager that will automatically push the content of the current mesh into a VBO with the exact attributes. A new VBO should be used
 * only if a VBO with the same attributes pointers doesn't exist.
 */
DefaultMesh::DefaultMesh(int componentCount, std::vector<float> vertices, std::vector<std::unique_ptr<VertexAttribute>> &attributes)
{
    this->vertices = std::make_unique<std::vector<float>>(std::move(vertices));
    this->indexOrders = std::make_unique<std::vector<unsigned int>>(0);

    if(&attributes == &defaultAttributes)
        CreateDefaultAttributes();

    manager = &MemoryManager::GetMemoryManager().Aquire(GL_STATIC_DRAW, std::make_unique<VboProperties>(attributes));
    manager->Push(*this);

}

void DefaultMesh::Bind()
{

}

void DefaultMesh::UnBind()
{

}
/**
 * TODO Memory clean
 * Remove from the main buffer.
 */
DefaultMesh::~DefaultMesh()
{

}
/**
 * TODO
 * Create a rendering manager that will receive rendering commands from the interface.
 *
 */


void DefaultMesh::SetDrawMode(GLenum drawMode)
{
    this->drawMode = drawMode;
}

std::vector<unsigned int> & DefaultMesh::SetVerticeDrawOrder(std::unique_ptr<std::vector<unsigned int>> indexOrders)
{
    this->indexOrders = std::move(indexOrders);
    manager->PushOrder(*this);
    return *this->indexOrders;
}

const std::vector<unsigned int> & DefaultMesh::GetVerticeOrders() const
{
    return *this->indexOrders;
}

void DefaultMesh::SetVertices(std::vector<float> vertices)
{
    SetVertices(std::make_unique<std::vector<float>>(std::move(vertices)));
}

void DefaultMesh::SetVerticeDrawOrder(std::vector<unsigned int> indexOrders)
{
    SetVerticeDrawOrder(std::make_unique<std::vector<unsigned int>>(std::move(indexOrders)));
}

void DefaultMesh::SetTextureComponentCount(const unsigned int &componentCount)
{
    this->textureComponentCount = componentCount;
}

void DefaultMesh::SetComponentCount(const unsigned int &componentCount)
{
    this->componentCount = componentCount;
}

void DefaultMesh::SetStride(const unsigned int &stride)
{
    this->stride = stride;
}

void DefaultMesh::OnRender(const RenderObjectEventInfo *renderObjectEventInfo)
{
    RenderObjectEventInfo eventInfo{static_cast<Mesh*>(this), nullptr};
    manager->OnRender(&eventInfo);
}

const std::string &DefaultMesh::GetTag()
{
    return tag;
}

void OpenGL::DefaultMesh::SetTag(const std::string &tag)
{
    this->tag = tag;
}

OpenGL::MeshMemoryManager & DefaultMesh::GetMeshManager() const
{
    return *manager;
}

DefaultMesh::DefaultMesh(int componentCount, std::vector<float> vertices) :
    DefaultMesh(componentCount, vertices, defaultAttributes)
{

}

const unsigned int & DefaultMesh::GetDrawMode()
{
    return drawMode;
}

void DefaultMesh::CreateDefaultAttributes()
{
    //Vertex
    defaultAttributes.emplace_back(std::make_unique<FloatVertexAttribute>(3,  8, 0));
    //Texture
    defaultAttributes.emplace_back(std::make_unique<FloatVertexAttribute>(2, 8, 3));
    //Normal
    defaultAttributes.emplace_back(std::make_unique<FloatVertexAttribute>(3,  8, 5));

}

const int & DefaultMesh::GetPriority()
{
    return RenderingPriorities::Mesh;
}
