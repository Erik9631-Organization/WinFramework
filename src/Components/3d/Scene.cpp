//
// Created by Erik on 18/04/22.
//

#include "Scene.h"
#include "RenderEventInfo.h"
#include "EventUpdateInfo.h"

Scene::Scene() :
    sceneGraph(this), renderingBehavior(*this)
{

}


void Scene::Repaint()
{

}

void Scene::AddRenderCommander(RenderCommander &renderable)
{

}

void Scene::RemoveRenderCommander(RenderCommander &renderable)
{

}

std::vector<std::reference_wrapper<RenderCommander>> Scene::GetRenderables()
{
    return renderingBehavior.GetRenderables();
}

void Scene::OnRender(RenderEventInfo e)
{
    renderingBehavior.OnRender(e);
}

void Scene::OnSync(const DrawData &data)
{
    renderingBehavior.OnSync(data);
}

void Scene::Rotate(const float &angle, const glm::vec3 &axis)
{

}

void Scene::SetRotation(const float &angle, const glm::vec3 &axis)
{

}

const glm::vec3 &Scene::GetRotationAxis()
{
    return glm::vec3{1};
}

const float &Scene::GetAngle()
{
    return 0;
}

void Scene::Scale(const glm::vec3 &scale)
{

}

void Scene::SetScale(const glm::vec3 &scale)
{

}

const glm::vec3 &Scene::GetScale()
{
    return glm::vec3{1};
}

void Scene::ResetTransform()
{

}

void Scene::Translate(const glm::vec3 &translation)
{

}

void Scene::SetTranslation(const glm::vec3 &translation)
{

}

const glm::vec3 &Scene::GetTranslation()
{
    return glm::vec3{1};
}


void Scene::Add(Element3d *element)
{
    addToContainerMutex.lock();
    sceneGraph.Add(element->GetElementNode());
    addToContainerMutex.unlock();
}

MultiTree<Element3d *> &Scene::GetElementNode()
{
    return sceneGraph;
}

void Scene::OnTick()
{
    NotifyOnTick();
}

void Scene::AddOnTickSubscriber(OnTickSubscriber *subscriber)
{
    tickSubjectBehavior.AddOnTickSubscriber(subscriber);
}

void Scene::RemoveOnTickSubscriber(OnTickSubscriber *subscriber)
{
    tickSubjectBehavior.RemoveOnTickSubscriber(subscriber);
}

void Scene::NotifyOnTick()
{
    addToContainerMutex.lock();
    tickSubjectBehavior.NotifyOnTick();
    for(int i = 0; i < sceneGraph.GetNodeCount(); i++)
    {
        auto* shit = sceneGraph.Get(i).GetValue();
        shit->OnTick();
    }
    addToContainerMutex.unlock();
}
