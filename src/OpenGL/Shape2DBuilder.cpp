//
// Created by Erik on 20/02/22.
//

#include "Shape2DBuilder.h"
#include "DefaultShaderProgram.h"
#include "DefaultMesh.h"
#include "GraphicsShader.h"
#include "DefaultModel.h"

std::unique_ptr<Model> Shape2DBuilder::CreateRectangle(float x, float y, float width, float height)
{
    auto program = std::make_unique<DefaultShaderProgram>();
    program->Add<GraphicsShader>(L"Shaders\\default.frag", GL_FRAGMENT_SHADER);
    program->Add<GraphicsShader>(L"Shaders\\default.vert", GL_VERTEX_SHADER);
    program->Link();

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

std::unique_ptr<Model> Shape2DBuilder::CreateRectangle(glm::vec2 position, glm::vec2 size)
{
    return CreateRectangle(position.x, position.y, size.x, size.y);
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
    auto program = std::make_unique<DefaultShaderProgram>();
    program->Add<GraphicsShader>(L"Shaders\\default.frag", GL_FRAGMENT_SHADER);
    program->Add<GraphicsShader>(L"Shaders\\default.vert", GL_VERTEX_SHADER);
    program->Link();

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
