//
// Created by Erik on 20/02/22.
//

#include "DefaultModel.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "UniformProperties.h"
#include <gtc/type_ptr.hpp>
#include "DefaultTexture.h"
#include "CameraManager.h"
#include "EventUpdateInfo.h"
#include <any>
#include "AutoId.h"

using namespace OpenGL;

/**
 * TODO
 * Model should accept a material class.
 * The material should encapsulate all the shader calls
 * The material should have specializations that unify the properties
 * It would be cool if the material had a reflection system.
 * The rendering manager should sort by shaders used in the material to decrease the amount of context swapping required
 * The texture, camera, shaders should be a unique ptr and should be owned by their own managers. Only reference should be here
 */


void DefaultModel::Translate(const glm::vec3 &translation)
{
    this->translationVec += translation;
    modelMatrix = glm::translate(modelMatrix, translation);
}

void DefaultModel::Scale(const glm::vec3 &scale)
{
    this->scalingVec += scale;
    modelMatrix = glm::scale(modelMatrix, scale);
}

void DefaultModel::Rotate(const float& angle, const glm::vec3 &axis)
{
    this->rotationAxis += axis;
    this->angle += angle;
    modelMatrix = glm::rotate(modelMatrix, angle, axis);
}

void DefaultModel::SetShaderProgram(ShaderProgram *shader)
{
    this->shaderProgram = shader;
}

ShaderProgram & DefaultModel::GetShader() const
{
    return *shaderProgram;
}

void DefaultModel::ResetTransform()
{
    modelMatrix = glm::mat4{1};
}

void DefaultModel::SetMesh(Mesh *mesh)
{
    RemoveRenderObjectSubscriber(*this->mesh);
    this->mesh = mesh;
    AddRenderObjectSubscriber(*this->mesh);
}

DefaultModel::DefaultModel(ShaderProgram *shaderProgram, Mesh *mesh)
{
    this->id = Utils::AutoId::AquireId();
    activeCamera = OpenGL::CameraManager::GetActiveCamera();
    viewMatrix = &defaultViewMatrix;
    projectionMatrix = &defaultProjectionMatrix;
    this->mesh = mesh;
    this->shaderProgram = shaderProgram;
    AddRenderObjectSubscriber(*this->mesh);
    this->material = std::make_unique<Material>(*shaderProgram);
    AddRenderObjectSubscriber(*this->material);
}

void DefaultModel::SetProjectionMatrix(glm::mat4 *projection)
{
    projectionMatrix = projection;
}

void DefaultModel::SetDrawMode(unsigned int drawMode)
{
    mesh->SetDrawMode(drawMode);
}

void DefaultModel::SetViewMatrix(glm::mat4 *view)
{
    this->viewMatrix = view;
}

void DefaultModel::SetTexture(Texture *texture)
{
    this->texture = texture;
}

void DefaultModel::OnCameraChanged(const Camera &newCamera)
{
    activeCamera = &newCamera;
}

const Mesh * OpenGL::DefaultModel::GetMesh() const
{
    return mesh;
}

std::unique_ptr<Model> DefaultModel::CloneUnique() const
{
    return std::make_unique<DefaultModel>(*this);
}

std::shared_ptr<Model> DefaultModel::CloneShared() const
{
    return std::make_shared<DefaultModel>(*this);
}

Model *DefaultModel::Clone() const
{
    return new DefaultModel(*this);
}

/**
 * TODO Move only if there are changes
 */
DefaultModel:: DefaultModel(const DefaultModel &model)
{
    id = model.id;
    shaderProgram = model.shaderProgram;
    mesh = model.mesh;
    modelMatrix = model.modelMatrix;
    basisMatrix = model.basisMatrix;
    viewMatrix = model.viewMatrix;
    projectionMatrix = model.projectionMatrix;
    texture = model.texture;
    activeCamera = model.activeCamera;
    renderObjectSubscribers = model.renderObjectSubscribers;
}

const glm::mat4 & DefaultModel::GetModelMatrix()  const
{
    return modelMatrix;
}

const glm::mat4 & DefaultModel::GetBasisMatrix()  const
{
    return basisMatrix;
}

const glm::mat4 * DefaultModel::GetViewMatrix()  const
{
    return viewMatrix;
}

const glm::mat4 * DefaultModel::GetProjectionMatrix()  const
{
    return projectionMatrix;
}

void DefaultModel::Move(const Model &model)
{
    *projectionMatrix = *model.GetProjectionMatrix();
    *viewMatrix = *model.GetViewMatrix();
    modelMatrix = model.GetModelMatrix();
    basisMatrix = model.GetBasisMatrix();
}

void DefaultModel::OnUpdate(EventUpdateInfo e)
{
    if(activeCamera != nullptr)
    {
        *viewMatrix = glm::lookAt(activeCamera->GetPosition(), activeCamera->GetPosition() + activeCamera->GetForwardAxis(), activeCamera->GetUpAxis());
    }
}

/**
 *  TODO Safety
 *  Ensure that renderObjectEventInfo contains the manager and is not null. Otherwise rendering should be ignored.
 *  Only the manager should be allowed to call the OnRender
 */
void DefaultModel::OnRender(const RenderObjectEventInfo *renderObjectEventInfo)
{
    if(activeCamera != nullptr)
        *viewMatrix = glm::lookAt(activeCamera->GetPosition(), activeCamera->GetPosition() + activeCamera->GetForwardAxis(), activeCamera->GetUpAxis());

    if(projectionMatrix == nullptr)
        shaderProgram->GetUniformProperties().SetProperty("projection", glm::mat4{1});
    else
        shaderProgram->GetUniformProperties().SetProperty("projection", *projectionMatrix);

    if(viewMatrix == nullptr)
        shaderProgram->GetUniformProperties().SetProperty("view", glm::mat4{1});
    else
        shaderProgram->GetUniformProperties().SetProperty("view", *viewMatrix);

    shaderProgram->GetUniformProperties().SetProperty("model", basisMatrix * modelMatrix);

    NotifyOnRenderObjects({this, mesh});
}

void DefaultModel::AddRenderObjectSubscriber(RenderObjectSubscriber &subscriber)
{
    renderObjectSubscribers.emplace(subscriber.GetPriority(), &subscriber);
}

void DefaultModel::RemoveRenderObjectSubscriber(const RenderObjectSubscriber &subscriber)
{
    for(auto it = renderObjectSubscribers.begin(); it != renderObjectSubscribers.end(); it++)
    {
        if(it->second == &subscriber)
        {
            renderObjectSubscribers.erase(it);
            return;
        }
    }
}

void DefaultModel::NotifyOnRenderObjects(const RenderObjectEventInfo &eventInfo)
{
    for(auto& subscribers : renderObjectSubscribers)
        subscribers.second->OnRender(&eventInfo);
}

Material &DefaultModel::GetMaterial()
{
    return *material;
}

void DefaultModel::SetMaterial(std::unique_ptr<Material> material)
{
    RemoveRenderObjectSubscriber(*this->material);
    this->material = std::move(material);
    AddRenderObjectSubscriber(*this->material);
}

const unsigned long long int & DefaultModel::GetId() const
{
    return id;
}

const Texture *DefaultModel::GetTexture() const
{
    return texture;
}

const int & DefaultModel::GetPriority()
{
    return 0;
}

void DefaultModel::SetRotation(const float &angle, const glm::vec3 &axis)
{
    this->rotationAxis = axis;
    this->angle = angle;
    RecalculateMatrix();
}

void DefaultModel::SetScale(const glm::vec3 &scale)
{
    this->scalingVec = scale;
    RecalculateMatrix();
}

void DefaultModel::SetTranslation(const glm::vec3 &translation)
{
    this->translationVec = translation;
    RecalculateMatrix();
}

void DefaultModel::RecalculateMatrix()
{
    ResetTransform();
    modelMatrix = glm::translate(modelMatrix, translationVec);
    modelMatrix = glm::rotate(modelMatrix, angle, rotationAxis);
    modelMatrix = glm::scale(modelMatrix, scalingVec);
}

const glm::vec3 &DefaultModel::GetRotationAxis()
{
    return rotationAxis;
}

const float &DefaultModel::GetAngle()
{
    return angle;
}

const glm::vec3 &DefaultModel::GetScale()
{
    return scalingVec;
}

const glm::vec3 &DefaultModel::GetTranslation()
{
    return translationVec;
}