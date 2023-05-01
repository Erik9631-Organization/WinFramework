//
// Created by Erik on 20/02/22.
//
#define _USE_MATH_DEFINES
#include "ModelBuilder.h"
#include "DefaultShaderProgram.h"
#include "StaticMesh.h"
#include "GraphicsShader.h"
#include "DefaultModel.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "GlobalResourceManager.h"
#include <cmath>

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateFillRectangle(float x, float y, float width, float height)
{
    float defaultWidth = 1;
    float defaultHeight = 1;

    Mesh* shape = meshManager->GetMesh("fillRectangle");

    if(shape == nullptr)
    {
        shape = &meshManager->CreateMesh<OpenGL::StaticMesh>("fillRectangle", std::vector<float>
        {
                0, 0, 0,                        0, 0,   0, 0, 0,
                defaultWidth, 0, 0,             0, 0,   0, 0, 0,
                defaultWidth, defaultHeight,0,  0, 0,   0, 0, 0,
                0, defaultHeight, 0,            0, 0,   0, 0, 0

        },
        std::vector<unsigned int>
        {
            0, 1, 2,
            0, 3, 2
        });
    }



    auto model = std::make_unique<DefaultModel>(shaderProgram, shape);
    if(projectionMatrix != nullptr)
        model->SetProjectionMatrix(projectionMatrix);
    model->Translate({x, y, 0});
    model->Scale(glm::vec3{width, height, 1.0});
    return model;
}



std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateFillRectangle(glm::vec4 position, glm::vec4 size)
{
    return CreateFillRectangle(position.x, position.y, size.x, size.y);
}

void OpenGL::ModelBuilder::SetProjectionMatrix(glm::mat4 *projection)
{
    projectionMatrix = projection;
}

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateTriangle(initializer_list<glm::vec4> vertices)
{
    return std::unique_ptr<Model>();
}

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateTriangle(glm::vec4 a1, glm::vec4 a2, glm::vec4 a3)
{

    Mesh& shape = meshManager->CreateMesh<OpenGL::StaticMesh>("", std::vector<float>
    {
        0, 0, 0,
        a2.x - a1.x, a2.y - a1.y, 0,
        a3.x - a1.x, a3.y - a1.y, 0,
    });

    auto model = std::make_unique<DefaultModel>(shaderProgram, &shape);
    model->SetProjectionMatrix(projectionMatrix);
    return model;
}

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateFillEllipse(float x, float y, float width, float height)
{
    std::vector<float> vertices;
    std::vector<unsigned int> drawOrder;

    //CreateElement the ellipse vector shape
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

    Mesh& shape = meshManager->CreateMesh<OpenGL::StaticMesh>("", vertices);
    shape.SetIndexBufferContent(drawOrder);

    auto model = std::make_unique<DefaultModel>(shaderProgram, &shape);
    model->SetProjectionMatrix(projectionMatrix);
    model->Translate({x, y, 0.0f});

    return model;
}

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateFillEllipse(glm::vec4 position, glm::vec4 size)
{
    return CreateFillEllipse(position.x, position.y, size.x, size.y);
}

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateRectangle(glm::vec4 position, glm::vec4 size)
{
    return CreateRectangle(position.x, position.y, size.x, size.y);
}

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateRectangle(float x, float y, float width, float height)
{

    float defaultWidth = 1;
    float defaultHeight = 1;

    Mesh* shape = meshManager->GetMesh("rectangle");

    if(shape == nullptr)
    {
        shape = &meshManager->CreateMesh<OpenGL::StaticMesh>("rectangle", std::vector<float>
        {
            0, 0, 0,                         0, 0,   0, 0, 0,
            defaultWidth, 0, 0,              0, 0,   0, 0, 0,
            defaultWidth, defaultHeight, 0,  0, 0,   0, 0, 0,
            0, defaultHeight, 0,             0, 0,   0, 0, 0
        },
        std::vector<unsigned int>
        {
            0, 1,
            1, 2,
            2, 3
        });
    }
    shape->SetPrimitiveType(GL_LINE_LOOP);

    auto model = std::make_unique<DefaultModel>(shaderProgram, shape);
    if(projectionMatrix != nullptr)
        model->SetProjectionMatrix(projectionMatrix);
    model->Scale({width, height, 1});
    model->Translate({x, y, 0});
    return model;
}

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateEllipse(glm::vec4 position, glm::vec4 size)
{
    return CreateEllipse(position.x, position.y, size.x, size.y);
}

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateEllipse(float x, float y, float width, float height)
{
    std::vector<float> vertices;
    std::vector<unsigned int> drawOrder;

    //CreateElement the ellipse vector shape
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
    Mesh& shape = meshManager->CreateMesh<OpenGL::StaticMesh>("", vertices);
    shape.SetIndexBufferContent(drawOrder);
    shape.SetPrimitiveType(GL_LINE_LOOP);

    auto model = std::make_unique<DefaultModel>(shaderProgram, &shape);
    model->SetProjectionMatrix(projectionMatrix);
    model->Translate({x, y, 0.0f});

    return model;
}

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateBlock(float x, float y, float z, float width, float height, float depth)
{
    float defaultWidth = 1;
    float defaultHeight = 1;
    float defaultDepth = 1;
    defaultDepth *= -1;
    defaultHeight *= -1;

    Mesh* shape = meshManager->GetMesh("block");

    if(shape == nullptr)
    {
        shape = &meshManager->CreateMesh<OpenGL::StaticMesh>("block", std::vector<float>
            {
                0, 0, 0,                                    0, 1,   0, 0, 1,//Front Face
                defaultWidth, 0, 0,                         1, 1,   0, 0, 1,
                defaultWidth, defaultHeight, 0,             1, 0,   0, 0, 1,
                0, 0, 0,                                    0, 1,   0, 0, 1,
                0, defaultHeight, 0,                        0, 0,   0, 0, 1,
                defaultWidth, defaultHeight, 0,             1, 0,   0, 0, 1,


                0, 0, defaultDepth,                         0, 1,   0, 0, -1, //Back Face
                defaultWidth, 0, defaultDepth,              1, 1,   0, 0, -1,
                defaultWidth, defaultHeight, defaultDepth,  1, 0,   0, 0, -1,
                0, 0, defaultDepth,                         0, 1,   0, 0, -1,
                0, defaultHeight, defaultDepth,             0, 0,   0, 0, -1,
                defaultWidth, defaultHeight, defaultDepth,  1, 0,   0, 0, -1,

                0, 0, 0,                                    0, 1,   -1, 0, 0, //Left Face
                0, defaultHeight, 0,                        0, 0,   -1, 0, 0,
                0, 0, defaultDepth,                         1, 1,   -1, 0, 0,
                0, 0, defaultDepth,                         1, 1,   -1, 0, 0,
                0, defaultHeight, defaultDepth,             1, 0,   -1, 0, 0,
                0, defaultHeight, 0,                        0, 0,   -1, 0, 0,

                defaultWidth, 0, 0,                         0, 1,   1, 0, 0, //Right Face
                defaultWidth, defaultHeight, 0,             0, 0,   1, 0, 0,
                defaultWidth, 0, defaultDepth,              1, 1,   1, 0, 0,
                defaultWidth, 0, defaultDepth,              1, 1,   1, 0, 0,
                defaultWidth, defaultHeight, defaultDepth,  1, 0,   1, 0, 0,
                defaultWidth, defaultHeight, 0,             0, 0,   1, 0, 0,

                0, 0, 0,                                    0, 1,   0, 1, 0, //Up Face
                defaultWidth, 0, 0,                         0, 0,   0, 1, 0,
                defaultWidth, 0, defaultDepth,              1, 0,   0, 1, 0,
                defaultWidth, 0, defaultDepth,              1, 0,   0, 1, 0,
                0, 0, defaultDepth,                         1, 1,   0, 1, 0,
                0, 0, 0,                                    0, 1,   0, 1, 0,

                0, defaultHeight, 0,                        0, 1,   0, -1, 0,//Bottom Face
                defaultWidth, defaultHeight, 0,             0, 0,   0, -1, 0,
                defaultWidth, defaultHeight, defaultDepth,      1, 0,   0, -1, 0,
                defaultWidth, defaultHeight, defaultDepth,  1, 0,   0, -1, 0,
                0, defaultHeight, defaultDepth,             1, 1,   0, -1, 0,
                0, defaultHeight, 0,                        0, 1,   0, -1, 0,
            });
    }

    auto model = std::make_unique<DefaultModel>(shaderProgram, shape);
    model->SetProjectionMatrix(projectionMatrix);
    model->Translate({x, y, z});
    model->Scale({width, height, depth});

    return model;

}

std::unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateBlock(glm::vec4 position, glm::vec4 size)
{
    return CreateBlock(position.x, position.y, position.z, size.x, size.y, size.z);
}

OpenGL::ModelBuilder::ModelBuilder()
{
    shaderProgram = static_cast<ShaderProgram*>(GlobalResourceManager::GetGlobalResourceManager()
        .GetDefaultShaderManager()->GetResource("default"));
    meshManager = GlobalResourceManager::GetGlobalResourceManager().GetDefaultMeshManager();
}

unique_ptr<OpenGL::Model> OpenGL::ModelBuilder::CreateEmptyModel()
{
    auto model = std::make_unique<DefaultModel>(shaderProgram, nullptr);
    model->SetProjectionMatrix(projectionMatrix);
    return std::move(model);
}
