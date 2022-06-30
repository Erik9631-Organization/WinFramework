//
// Created by Erik on 18/04/22.
//

#ifndef LII_SCENE_H
#define LII_SCENE_H
#include "Element3d.h"
#include "DefaultMultiTree.h"
#include "DefaultRender.h"
#include "TickSubjectBehavior.h"
#include <mutex>


class Scene : public Element3d
{
private:
    DefaultMultiTree<std::unique_ptr<Element3d>>* sceneGraph;
    DefaultRender renderingBehavior;
    std::mutex addToContainerMutex;
    TickSubjectBehavior tickSubjectBehavior;
public:
    Scene();
    ~Scene();
    void Repaint() override;
    void AddRenderCommander(RenderCommander &renderable) override;
    void RemoveRenderCommander(RenderCommander &renderable) override;
    std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;
    void OnRenderSync(RenderEventInfo e) override;
    void OnSync(const DrawData &data) override;
    void Rotate(const float &angle, const glm::vec3 &axis) override;
    void SetRotation(const float &angle, const glm::vec3 &axis) override;
    const glm::vec3 &GetRotationAxis() override;
    const float &GetAngle() override;
    void Scale(const glm::vec3 &scale) override;
    void SetScale(const glm::vec3 &scale) override;
    const glm::vec3 &GetScale() override;
    void ResetTransform() override;
    void Translate(const glm::vec3 &translation) override;
    void SetTranslation(const glm::vec3 &translation) override;
    const glm::vec3 &GetTranslation() override;
    MultiTree<std::unique_ptr<Element3d>> & GetElementNode() override;
    void Add(std::unique_ptr<Element3d> element) override;
    void OnTick() override;
    void AddOnTickSubscriber(OnTickSubscriber *subscriber) override;
    void RemoveOnTickSubscriber(OnTickSubscriber *subscriber) override;
    void NotifyOnTick() override;

};


#endif //LII_SCENE_H
