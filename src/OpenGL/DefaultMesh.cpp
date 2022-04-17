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


    /*this->vertices = std::make_unique<std::vector<float>>(std::move(vertices));
    this->indexOrders = std::make_unique<std::vector<unsigned int>>(0);

    unsigned int bufferSize = (sizeof(float) * this->vertices->size());

    this->componentCount = componentCount;
    glGenVertexArrays(1, &VaoId);
    glGenBuffers(1, &VboId);

    glBindVertexArray(VaoId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, this->vertices->data(), GL_STATIC_DRAW);
    glVertexAttribPointer(vertexAttributeId, componentCount, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)0x0);
    glEnableVertexAttribArray(vertexAttributeId);
    glVertexAttribPointer(textureAttributeId, textureComponentCount, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(componentCount*sizeof(float)));
    glEnableVertexAttribArray(textureAttributeId);
    unsigned int normalsOffset = (componentCount*sizeof(float)) + textureComponentCount*sizeof(float);
    glVertexAttribPointer(normalsAttributeId, normalsComponentCount, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(normalsOffset));
    glEnableVertexAttribArray(normalsAttributeId);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);*/

}

void DefaultMesh::Bind()
{
    //glBindVertexArray(VaoId);
}

void DefaultMesh::UnBind()
{
    //glBindVertexArray(0);
}
/**
 * TODO Memory clean
 * Remove from the main buffer.
 */
DefaultMesh::~DefaultMesh()
{
    //glBindVertexArray(0);
    //glDeleteBuffers(1, &VboId);
    //glDeleteVertexArrays(1, &VaoId);
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
//    this->indexOrders = std::move(indexOrders);
//
//    glDeleteBuffers(1, &EboId); // Make sure that the last bound array was cleared
//
//    Bind();
//    glGenBuffers(1, &EboId);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
//
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->indexOrders->size(), this->indexOrders->data(), GL_STATIC_DRAW);
//
//    UnBind();
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return *this->indexOrders;
}

const std::vector<unsigned int> & DefaultMesh::GetVerticeOrders() const
{
    return *this->indexOrders;
}

void DefaultMesh::DrawArrays()
{
    int verticeCount = this->vertices->size() / componentCount;
    glDrawArrays(drawMode, 0, verticeCount);
}

void DefaultMesh::DrawElements()
{
    glDrawElements(drawMode, indexOrders->size(), GL_UNSIGNED_INT, 0x0);
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
//For debug only, should be removed and only the rendering manager should be capable of rendering

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

    //glVertexAttribPointer(vertexAttributeId, componentCount, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)0x0);
    //glVertexAttribPointer(textureAttributeId, textureComponentCount, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(componentCount*sizeof(float)));
    //unsigned int normalsOffset = (componentCount*sizeof(float)) + textureComponentCount*sizeof(float);
    //glVertexAttribPointer(normalsAttributeId, normalsComponentCount, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(normalsOffset));

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
