//
// Created by Erik on 20/02/22.
//

#ifndef LII_DEFAULTMODEL_H
#define LII_DEFAULTMODEL_H
#include "Model.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <map>
#include "CameraManagerSubscriber.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "StaticTexture.h"
#include "Material.h"

namespace OpenGL
{
    class DefaultModel : public Model
    {
    private:
        ShaderProgram* shaderProgram;
        Mesh* mesh;
        glm::mat4 modelMatrix{1.0f};
        glm::mat4 basisMatrix{1.0f};

        glm::mat4 defaultViewMatrix{1.0f};
        glm::mat4* viewMatrix = nullptr;
        glm::mat4 defaultProjectionMatrix{1.0f};
        glm::mat4* projectionMatrix = nullptr;
        Texture* texture = nullptr;
        const Camera* activeCamera;
        std::multimap<int, RenderObjectSubscriber*> renderObjectSubscribers;
        std::unique_ptr<Material> material;
        unsigned long long id;

        glm::vec3 translationVec = glm::vec3{1};
        glm::vec3 rotationAxis = glm::vec3{1};
        glm::vec3 scalingVec = glm::vec3{1};
        float angle = 0;
        bool customCameraEnabled = false;

        void RecalculateMatrix();
    public:
        DefaultModel(ShaderProgram *shaderProgram, Mesh *mesh);
        DefaultModel(const DefaultModel &model);
        void Translate(const glm::vec3 &translation) override;
        void Scale(const glm::vec3 &scale) override;
        void Rotate(const float& angle, const glm::vec3 &axis) override;
        void SetShaderProgram(ShaderProgram *shader) override;
        ShaderProgram & GetShaderProgram() const override;
        void ResetTransform() override;
        void SetMesh(Mesh *mesh);
        void SetProjectionMatrix(glm::mat4 *projection) override;
        void SetDrawMode(unsigned int drawMode) override;
        void SetViewMatrix(glm::mat4 *view) override;
        void SetTexture(Texture *texture) override;
        void OnCameraChanged(const Camera *newCamera) override;
        const Mesh * GetMesh() const override;
        std::unique_ptr<Model> CloneUnique() const;
        std::shared_ptr<Model> CloneShared() const;
        Model *Clone() const;
        const glm::mat4 & GetModelMatrix() const override;
        const glm::mat4 & GetBasisMatrix() const override;
        const glm::mat4 * GetViewMatrix() const override;
        const glm::mat4 * GetProjectionMatrix() const override;
        void Move(const Model &model) override;
        void OnUpdate(EventUpdateInfo e) override;
        void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
        void AddRenderObjectSubscriber(RenderObjectSubscriber& subscriber) override;
        void RemoveRenderObjectSubscriber(const RenderObjectSubscriber &subscriber) override;
        void NotifyOnRenderObjects(const RenderObjectEventInfo &eventInfo) override;
        Material &GetMaterial() override;
        void SetMaterial(std::unique_ptr<Material> material) override;
        const unsigned long long int & GetId() const override;
        const Texture *GetTexture() const override;
        const int & GetPriority() override;
        void SetRotation(const float &angle, const glm::vec3 &axis) override;
        void SetScale(const glm::vec3 &scale) override;
        void SetTranslation(const glm::vec3 &translation) override;
        const glm::vec3 &GetRotationAxis() override;
        const float &GetAngle() override;
        const glm::vec3 &GetScale() override;
        const glm::vec3 &GetTranslation() override;
        void CustomCameraEnabled(const bool &state) override;
        const bool &IsCustomCameraEnabled() override;
        void SetCamera(const Camera *camera) override;
        const Camera * GetCamera() override;
        void SetTexture(const string &textureTag) override;
        void SetMesh(const string &meshTag) override;
        void SetShaderProgram(const string shaderTag) override;
    };
}


#endif //LII_DEFAULTMODEL_H
