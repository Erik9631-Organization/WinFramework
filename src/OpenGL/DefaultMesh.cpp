//
// Created by Erik on 18/02/22.
//

#include "DefaultMesh.h"
#include <glew.h>
#include <wglew.h>
#include "RenderEventInfo.h"

std::vector<float> &DefaultMesh::SetVertices(std::unique_ptr<std::vector<float>> vertices)
{
    this->vertices = std::move(vertices);
    return *this->vertices;
}

const std::vector<float> &DefaultMesh::GetVertices()
{
    return *vertices;
}

int DefaultMesh::GetComponentCount()
{
    return componentCount;
}

DefaultMesh::DefaultMesh(int componentCount) :
    DefaultMesh(componentCount, {})
{
    this->componentCount = componentCount;
}

DefaultMesh::DefaultMesh(int componentCount, std::vector<float> vertices)
{
    this->vertices = std::make_unique<std::vector<float>>(std::move(vertices));
    this->indexOrders = std::make_unique<std::vector<unsigned int>>(0);

    this->componentCount = componentCount;
    glGenVertexArrays(1, &VaoId);
    glGenBuffers(1, &VboId);

    glBindVertexArray(VaoId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * this->vertices->size()), this->vertices->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, componentCount, GL_FLOAT, GL_FALSE, sizeof(float) * componentCount, (void*)0x0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void DefaultMesh::Bind()
{
    glBindVertexArray(VaoId);
}

void DefaultMesh::UnBind()
{
    glBindVertexArray(0);
}

DefaultMesh::~DefaultMesh()
{
    glBindVertexArray(0);
    glDeleteBuffers(1, &VboId);
    glDeleteVertexArrays(1, &VaoId);
}

void DefaultMesh::Draw()
{
    Bind();
    if(EboId == 0)
        DrawArrays();
    else
        DrawElements();
    UnBind();
}

void DefaultMesh::DrawMode(GLenum drawMode)
{
    this->drawMode = drawMode;
}

std::vector<unsigned int> & DefaultMesh::SetVerticeDrawOrder(std::unique_ptr<std::vector<unsigned int>> indexOrders)
{
    this->indexOrders = std::move(indexOrders);

    glDeleteBuffers(1, &EboId); // Make sure that the last bound array was cleared

    Bind();
    glGenBuffers(1, &EboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->indexOrders->size(), this->indexOrders->data(), GL_STATIC_DRAW);

    UnBind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return *this->indexOrders;
}

const std::vector<unsigned int> & DefaultMesh::GetVerticeOrders()
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

