//
// Created by Erik on 17/04/22.
//

#include "ModeledElement.h"
#include "RenderEventInfo.h"
#include "EventUpdateInfo.h"
#include "RenderingPool.h"

void ModeledElement::Repaint()
{

}

void ModeledElement::AddRenderCommander(RenderCommander &renderable)
{
    renderingBehavior.AddRenderCommander(renderable);
}

void ModeledElement::RemoveRenderCommander(RenderCommander &renderable)
{
    renderingBehavior.RemoveRenderCommander(renderable);
}

std::vector<std::reference_wrapper<RenderCommander>> ModeledElement::GetRenderables()
{
    return renderingBehavior.GetRenderables();
}

void ModeledElement::OnRender(RenderEventInfo e)
{
    renderingBehavior.OnRender(e);
    if(model == nullptr)
        return;
    e.GetRenderer()->Acquire(*this).DrawModel(*model);
}

void ModeledElement::OnSync(const DrawData &data)
{
    renderingBehavior.OnSync(data);
}

void ModeledElement::Rotate(const float &angle, const glm::vec3 &axis)
{
    if(model == nullptr)
        return;
    model->Rotate(angle, axis);
}

void ModeledElement::Scale(const glm::vec3 &scale)
{
    if(model == nullptr)
        return;
    model->Scale(scale);
}

void ModeledElement::ResetTransform()
{
    if(model == nullptr)
        return;
    model->ResetTransform();
}

void ModeledElement::Translate(const glm::vec3 &translation)
{
    if(model == nullptr)
        return;
    model->Translate(translation);
}

void ModeledElement::SetRotation(const float &angle, const glm::vec3 &axis)
{
    if(model == nullptr)
        return;
    model->SetRotation(angle, axis);
}

void ModeledElement::SetScale(const glm::vec3 &scale)
{
    if(model == nullptr)
        return;
    model->SetScale(scale);
}

void ModeledElement::SetTranslation(const glm::vec3 &translation)
{
    if(model == nullptr)
        return;
    model->SetTranslation(translation);
}

const glm::vec3 &ModeledElement::GetRotationAxis()
{
    if(model == nullptr)
        return glm::vec3 {1};

    return model->GetRotationAxis();
}

const float &ModeledElement::GetAngle()
{
    if(model == nullptr)
        return 0;

    return model->GetAngle();
}

const glm::vec3 &ModeledElement::GetScale()
{
    if(model == nullptr)
        return glm::vec3 {1};
    return model->GetScale();
}

const glm::vec3 &ModeledElement::GetTranslation()
{
    if(model == nullptr)
        return glm::vec3 {1};

    return model->GetTranslation();
}

void ModeledElement::Add(Element3d *element)
{
    addToContainerMutex.lock();
    treeNode.Add(element->GetElementNode());
    addToContainerMutex.unlock();
}

MultiTree<Element3d *> &ModeledElement::GetElementNode()
{
    return treeNode;
}

ModeledElement::ModeledElement() : ModeledElement(nullptr)

{

}

void ModeledElement::OnTick()
{
    NotifyOnTick();
}

void ModeledElement::AddOnTickSubscriber(OnTickSubscriber *subscriber)
{
    tickSubjectBehavior.AddOnTickSubscriber(subscriber);
}

void ModeledElement::RemoveOnTickSubscriber(OnTickSubscriber *subscriber)
{
    tickSubjectBehavior.RemoveOnTickSubscriber(subscriber);
}

void ModeledElement::NotifyOnTick()
{
    for(int i = 0; i < treeNode.GetNodeCount(); i++)
    {
        treeNode.Get(i).GetValue()->OnTick();
    }
}

ModeledElement::ModeledElement(std::unique_ptr<OpenGL::Model> model) : renderingBehavior(*this), treeNode(this)
{
    this->model = std::move(model);
}

OpenGL::Model *ModeledElement::GetModel()
{
    return model.get();
}
