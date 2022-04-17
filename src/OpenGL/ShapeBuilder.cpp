//
// Created by Erik on 20/02/22.
//
#define _USE_MATH_DEFINES
#include "ShapeBuilder.h"
#include "DefaultShaderProgram.h"
#include "DefaultMesh.h"
#include "GraphicsShader.h"
#include "DefaultModel.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "GlobalResourceManager.h"
#include <cmath>
#include <DestroyEventInfo.h>

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateFillRectangle(float x, float y, float width, float height)
{

    Mesh& shape = meshManager->CreateMesh<OpenGL::DefaultMesh>("",3, std::vector<float>
    {
        0, 0, 0,            0, 1,
        width, 0, 0,        1, 1,
        width, height, 0,   1, 0,
        0, height, 0,       0, 0
    });
    shape.SetVerticeDrawOrder(
    {
        0, 1, 2,
        0, 3, 2
    });

    auto model = std::make_unique<DefaultModel>(shaderProgram, &shape);
    if(projectionMatrix != nullptr)
        model->SetProjectionMatrix(projectionMatrix);
    model->Translate({x, y, 0});
    return model;
}



std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateFillRectangle(glm::vec2 position, glm::vec2 size)
{
    return CreateFillRectangle(position.x, position.y, size.x, size.y);
}

void OpenGL::ShapeBuilder::SetProjectionMatrix(glm::mat4 *projection)
{
    projectionMatrix = projection;
}

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateTriangle(std::initializer_list<glm::vec2> vertices)
{
    return std::unique_ptr<Model>();
}

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateTriangle(glm::vec2 a1, glm::vec2 a2, glm::vec2 a3)
{

    Mesh& shape = meshManager->CreateMesh<OpenGL::DefaultMesh>("", 3, std::vector<float>
    {
        0, 0, 0,
        a2.x - a1.x, a2.y - a1.y, 0,
        a3.x - a1.x, a3.y - a1.y, 0,
    });

    auto model = std::make_unique<DefaultModel>(shaderProgram, &shape);
    model->SetProjectionMatrix(projectionMatrix);
    return model;
}

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateFillEllipse(float x, float y, float width, float height)
{
    std::vector<float> vertices;
    std::vector<unsigned int> drawOrder;

    //Create the ellipse vector shape
    for(int degrees = 0; degrees < 360; degrees++)
    {
        float rads = (M_PI / 180 ) * degrees;
        float x = width*cos(rads);
        float y = height*sin(rads);
        vertices.insert(vertices.end(), {x, y, 0.0f});
    }
    vertices.insert(vertices.end(), {0, 0, 0}); // last element is the center vertex

    //Now create the index matrix
    for(unsigned int vertice = 1, prevVertice = 0; vertice != 360; vertice++, prevVertice++)
    {
        drawOrder.insert(drawOrder.end(), {360, vertice, prevVertice});
    }

    drawOrder.insert(drawOrder.end(), {360, 0, 359}); // To loop the ellipse

    Mesh& shape = meshManager->CreateMesh<OpenGL::DefaultMesh>("",3, vertices);
    shape.SetVerticeDrawOrder(drawOrder);

    auto model = std::make_unique<DefaultModel>(shaderProgram, &shape);
    model->SetProjectionMatrix(projectionMatrix);
    model->Translate({x, y, 0.0f});

    return model;
}

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateFillEllipse(glm::vec2 position, glm::vec2 size)
{
    return CreateFillEllipse(position.x, position.y, size.x, size.y);
}

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateRectangle(glm::vec2 position, glm::vec2 size)
{
    return CreateRectangle(position.x, position.y, size.x, size.y);
}

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateRectangle(float x, float y, float width, float height)
{

    Mesh& shape = meshManager->CreateMesh<OpenGL::DefaultMesh>("", 3, std::vector<float>
    {
        0, 0, 0,
        width, 0, 0,
        width, height, 0,
        0, height, 0
    });
    shape.SetVerticeDrawOrder(
        {
            0, 1,
            1, 2,
            2, 3,
        });
    shape.SetDrawMode(GL_LINE_LOOP);

    auto model = std::make_unique<DefaultModel>(shaderProgram, &shape);
    if(projectionMatrix != nullptr)
        model->SetProjectionMatrix(projectionMatrix);
    model->Translate({x, y, 0});
    return model;
}

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateEllipse(glm::vec2 position, glm::vec2 size)
{
    return CreateEllipse(position.x, position.y, size.x, size.y);
}

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateEllipse(float x, float y, float width, float height)
{
    std::vector<float> vertices;
    std::vector<unsigned int> drawOrder;

    //Create the ellipse vector shape
    for(int degrees = 0; degrees < 360; degrees++)
    {
        float rads = (M_PI / 180 ) * degrees;
        float x = width*cos(rads);
        float y = height*sin(rads);
        vertices.insert(vertices.end(), {x, y, 0.0f});
    }


    //Now create the index matrix
    for(unsigned int vertice = 1, prevVertice = 0; vertice != 360; vertice++, prevVertice++)
    {
        drawOrder.insert(drawOrder.end(), {prevVertice, vertice});
    }
    Mesh& shape = meshManager->CreateMesh<OpenGL::DefaultMesh>("",3, vertices);
    shape.SetVerticeDrawOrder(drawOrder);
    shape.SetDrawMode(GL_LINE_LOOP);

    auto model = std::make_unique<DefaultModel>(shaderProgram, &shape);
    model->SetProjectionMatrix(projectionMatrix);
    model->Translate({x, y, 0.0f});

    return model;
}

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateBlock(float x, float y, float z, float width, float height, float depth)
{

    depth *= -1;
    height *= -1;
    Mesh& shape = meshManager->CreateMesh<OpenGL::DefaultMesh>("",3, std::vector<float>
        {
            0, 0, 0,            0, 1,   0, 0, 1,//Front Face
            width, 0, 0,        1, 1,   0, 0, 1,
            width, height, 0,   1, 0,   0, 0, 1,
            0, 0, 0,            0, 1,   0, 0, 1,
            0, height, 0,       0, 0,   0, 0, 1,
            width, height, 0,   1, 0,   0, 0, 1,


            0, 0, depth,            0, 1,   0, 0, -1, //Back Face
            width, 0, depth,        1, 1,   0, 0, -1,
            width, height, depth,   1, 0,   0, 0, -1,
            0, 0, depth,            0, 1,   0, 0, -1,
            0, height, depth,       0, 0,   0, 0, -1,
            width, height, depth,   1, 0,   0, 0, -1,

            0, 0, 0,            0, 1,   -1, 0, 0, //Left Face
            0, height, 0,       0, 0,   -1, 0, 0,
            0, 0, depth,        1, 1,   -1, 0, 0,
            0, 0, depth,        1, 1,   -1, 0, 0,
            0, height, depth,   1, 0,   -1, 0, 0,
            0, height, 0,       0, 0,   -1, 0, 0,

            width, 0, 0,            0, 1,   1, 0, 0, //Right Face
            width, height, 0,       0, 0,   1, 0, 0,
            width, 0, depth,        1, 1,   1, 0, 0,
            width, 0, depth,        1, 1,   1, 0, 0,
            width, height, depth,   1, 0,   1, 0, 0,
            width, height, 0,       0, 0,   1, 0, 0,

            0, 0, 0,                0, 1,   0, 1, 0, //Up Face
            width, 0, 0,            0, 0,   0, 1, 0,
            width, 0, depth,        1, 0,   0, 1, 0,
            width, 0, depth,        1, 0,   0, 1, 0,
            0, 0, depth,            1, 1,   0, 1, 0,
            0, 0, 0,                0, 1,   0, 1, 0,

            0, height, 0,                0, 1,   0, -1, 0,//Bottom Face
            width, height, 0,            0, 0,   0, -1, 0,
            width, height, depth,        1, 0,   0, -1, 0,
            width, height, depth,        1, 0,   0, -1, 0,
            0, height, depth,            1, 1,   0, -1, 0,
            0, height, 0,                0, 1,   0, -1, 0,
        });

    auto model = std::make_unique<DefaultModel>(shaderProgram, &shape);
    model->SetProjectionMatrix(projectionMatrix);
    model->Translate({x, y, z});
    return model;

}

std::unique_ptr<OpenGL::Model> OpenGL::ShapeBuilder::CreateBlock(glm::vec3 position, glm::vec3 size)
{
    return CreateBlock(position.x, position.y, position.z, size.x, size.y, size.z);
}

OpenGL::ShapeBuilder::ShapeBuilder()
{
    shaderProgram = GlobalResourceManager::GetGlobalResourceManager().AquireResource<ShaderProgram>("shader", "default");
    meshManager = GlobalResourceManager::GetGlobalResourceManager().GetResourceManager<MeshManager>("mesh");
}
