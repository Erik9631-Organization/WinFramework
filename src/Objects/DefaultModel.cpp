//
// Created by Erik on 20/02/22.
//

#include "DefaultModel.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "UniformManager.h"
#include <gtc/type_ptr.hpp>

void DefaultModel::Translate(const glm::vec3 &translation)
{
    transformMatrix = glm::translate(transformMatrix, translation);
}

void DefaultModel::Scale(const glm::vec3 &scale)
{
    transformMatrix = glm::scale(transformMatrix, scale);
}

void DefaultModel::Rotate(float angle, const glm::vec3 &axis)
{
    transformMatrix = glm::rotate(transformMatrix, angle, axis);
}

void DefaultModel::SetShaderProgram(std::unique_ptr<ShaderProgram> shader)
{
    this->shaderProgram = std::move(shader);
}

ShaderProgram &DefaultModel::GetShader()
{
    shaderProgram->Use();
    return *shaderProgram;
}

void DefaultModel::Draw()
{
    shaderProgram->Use();

 //   glm::vec4 resultTest = transformMatrix * glm::vec4{0, 0, 0, 1};
 //   glm::vec4 resultTest2 =  viewMatrix * resultTest;

    if(viewMatrix == nullptr)
        shaderProgram->GetUniformManager().SetUniform(glUniformMatrix4fv, "view", (const float*)glm::value_ptr(glm::mat4{1}));
    else
        shaderProgram->GetUniformManager().SetUniform(glUniformMatrix4fv, "view", (const float*)glm::value_ptr(*viewMatrix));

    shaderProgram->GetUniformManager().SetUniform(glUniformMatrix4fv, "transform", (const float*)glm::value_ptr(transformMatrix));
    mesh->Draw();
}

void DefaultModel::ResetTransform()
{
    transformMatrix = std::move(glm::mat4{1});
}

void DefaultModel::SetMesh(std::unique_ptr<Mesh> mesh)
{
    this->mesh = std::move(mesh);
}

DefaultModel::DefaultModel(std::unique_ptr<ShaderProgram> shaderProgram, std::unique_ptr<Mesh> mesh)
{
    this->mesh = std::move(mesh);
    this->shaderProgram = std::move(shaderProgram);
    viewMatrix.reset();
}

void DefaultModel::SetViewMatrix(std::shared_ptr<glm::mat4> view)
{
    viewMatrix = view;
}
