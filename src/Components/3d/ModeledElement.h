//
// Created by Erik on 17/04/22.
//

#ifndef LII_MODELEDELEMENT_H
#define LII_MODELEDELEMENT_H
#include "Adjustable.h"
#include "RenderCommander.h"
#include "Transformable.h"
#include "Model.h"
#include "DefaultRender.h"
#include "Element3d.h"
#include "DefaultMultiTree.h"
#include "TickSubjectBehavior.h"

class ModeledElement : public Element3d
{
private:
    DefaultRender renderingBehavior;
    DefaultMultiTree<std::unique_ptr<Element3d>>* treeNode;
    TickSubjectBehavior tickSubjectBehavior;
    std::mutex addToContainerMutex;
protected:
    std::unique_ptr<OpenGL::Model> model;
public:
    ModeledElement();
    ~ModeledElement();
    ModeledElement(std::unique_ptr<OpenGL::Model> model);
    void Repaint() override;
    void AddRenderCommander(RenderCommander &renderable) override;
    void RemoveRenderCommander(RenderCommander &renderable) override;
    std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;
    void OnRender(RenderEventInfo e) override;
    void OnSync(const DrawData &data) override;
    void Rotate(const float &angle, const glm::vec3 &axis) override;
    void Scale(const glm::vec3 &scale) override;
    void ResetTransform() override;
    void Translate(const glm::vec3 &translation) override;
    void SetRotation(const float &angle, const glm::vec3 &axis) override;
    void SetScale(const glm::vec3 &scale) override;
    void SetTranslation(const glm::vec3 &translation) override;
    const glm::vec3 &GetRotationAxis() override;
    const float &GetAngle() override;
    const glm::vec3 &GetScale() override;
    const glm::vec3 &GetTranslation() override;
    void Add(std::unique_ptr<Element3d> element) override;
    MultiTree<std::unique_ptr<Element3d>> & GetElementNode() override;
    void OnTick() override;
    void AddOnTickSubscriber(OnTickSubscriber *subscriber) override;
    void RemoveOnTickSubscriber(OnTickSubscriber *subscriber) override;
    void NotifyOnTick() override;
    OpenGL::Model* GetModel();

};


#endif //LII_MODELEDELEMENT_H
