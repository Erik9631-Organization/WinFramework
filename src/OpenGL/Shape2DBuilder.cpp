//
// Created by Erik on 20/02/22.
//
#define _USE_MATH_DEFINES
#include "Shape2DBuilder.h"
#include "DefaultShaderProgram.h"
#include "DefaultMesh.h"
#include "GraphicsShader.h"
#include "DefaultModel.h"
#include <cmath>

std::unique_ptr<Model> Shape2DBuilder::CreateFillRectangle(float x, float y, float width, float height)
{
    auto program = CreateDefaultShaderProgram();

    auto shape = std::make_unique<DefaultMesh>(3, std::vector<float>
    {
        0, 0, 0,
        width, 0, 0,
        width, height, 0,
        0, height, 0
    });
    shape->SetVerticeDrawOrder(
    {
        0, 1, 2,
        0, 3, 2
    });

    auto model = std::make_unique<DefaultModel>(std::move(program), std::move(shape));
    if(viewMatrix != nullptr)
        model->SetViewMatrix(viewMatrix);
    model->Translate({x, y, 0});

    return model;
}



std::unique_ptr<Model> Shape2DBuilder::CreateFillRectangle(glm::vec2 position, glm::vec2 size)
{
    return CreateFillRectangle(position.x, position.y, size.x, size.y);
}

void Shape2DBuilder::SetViewMatrix(std::shared_ptr<glm::mat4> view)
{
    viewMatrix = view;
}

std::unique_ptr<Model> Shape2DBuilder::CreateTriangle(std::initializer_list<glm::vec2> vertices)
{
    return std::unique_ptr<Model>();
}

std::unique_ptr<Model> Shape2DBuilder::CreateTriangle(glm::vec2 a1, glm::vec2 a2, glm::vec2 a3)
{
    auto program = CreateDefaultShaderProgram();

    auto shape = std::make_unique<DefaultMesh>(3, std::vector<float>
    {
        0, 0, 0,
        a2.x - a1.x, a2.y - a1.y, 0,
        a3.x - a1.x, a3.y - a1.y, 0,
    });

    auto model = std::make_unique<DefaultModel>(std::move(program), std::move(shape));
    model->SetViewMatrix(viewMatrix);
    return model;
}

std::unique_ptr<ShaderProgram> Shape2DBuilder::CreateDefaultShaderProgram()
{
    auto program = std::make_unique<DefaultShaderProgram>();
    program->Add<GraphicsShader>(L"Shaders\\default.frag", GL_FRAGMENT_SHADER);
    program->Add<GraphicsShader>(L"Shaders\\default.vert", GL_VERTEX_SHADER);
    program->Link();
    return program;
}

std::unique_ptr<Model> Shape2DBuilder::CreateFillEllipse(float x, float y, float width, float height)
{
    auto program = CreateDefaultShaderProgram();
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

    auto shape = std::make_unique<DefaultMesh>(3, vertices);
    shape->SetVerticeDrawOrder(drawOrder);

    auto model = std::make_unique<DefaultModel>(std::move(program), std::move(shape));
    model->SetViewMatrix(viewMatrix);
    model->Translate({x, y, 0.0f});

    return model;
}

std::unique_ptr<Model> Shape2DBuilder::CreateFillEllipse(glm::vec2 position, glm::vec2 size)
{
    return CreateFillEllipse(position.x, position.y, size.x, size.y);
}

std::unique_ptr<Model> Shape2DBuilder::CreateRectangle(glm::vec2 position, glm::vec2 size)
{
    return CreateRectangle(position.x, position.y, size.x, size.y);
}

std::unique_ptr<Model> Shape2DBuilder::CreateRectangle(float x, float y, float width, float height)
{
    auto program = CreateDefaultShaderProgram();

    auto shape = std::make_unique<DefaultMesh>(3, std::vector<float>
    {
        0, 0, 0,
        width, 0, 0,
        width, height, 0,
        0, height, 0
    });
    shape->SetVerticeDrawOrder(
        {
            0, 1,
            1, 2,
            2, 3,
        });
    shape->DrawMode(GL_LINE_LOOP);

    auto model = std::make_unique<DefaultModel>(std::move(program), std::move(shape));
    if(viewMatrix != nullptr)
        model->SetViewMatrix(viewMatrix);
    model->Translate({x, y, 0});
    return model;
}

std::unique_ptr<Model> Shape2DBuilder::CreateEllipse(glm::vec2 position, glm::vec2 size)
{
    return CreateEllipse(position.x, position.y, size.x, size.y);
}

std::unique_ptr<Model> Shape2DBuilder::CreateEllipse(float x, float y, float width, float height)
{
    auto program = CreateDefaultShaderProgram();
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
    auto shape = std::make_unique<DefaultMesh>(3, vertices);
    shape->SetVerticeDrawOrder(drawOrder);
    shape->DrawMode(GL_LINE_LOOP);

    auto model = std::make_unique<DefaultModel>(std::move(program), std::move(shape));
    model->SetViewMatrix(viewMatrix);
    model->Translate({x, y, 0.0f});

    return model;
}
