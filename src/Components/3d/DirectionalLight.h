//
// Created by Erik on 29/06/22.
//

#ifndef LII_DIRECTIONALLIGHT_H
#define LII_DIRECTIONALLIGHT_H
#include "Light.h"
#include "ModeledElement.h"
#include "IdManager.h"


class DirectionalLight : public ModeledElement, public Light, public RenderObjectSubscriber
{
public:
    DirectionalLight(std::unique_ptr<OpenGL::Model> model, glm::vec3 direction);
    void SetEnabled(const bool &State) override;
    const bool &GetEnabled() const override;
    void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
    const int &GetPriority() override;
    static unsigned int GetMaxDirectionalLights();
    bool enabled = true;
    ~DirectionalLight();
    const glm::ivec4 GetColor() const override;
    void SetColor(const glm::ivec4 &color) override;
private:
    void SetLight(const glm::vec3 &direction);
    static IdManager idManager;
    static constexpr unsigned int maxDirectionalLights = 20;
    unsigned int assignedId = -1;
    glm::ivec4 lightColor;
};


#endif //LII_DIRECTIONALLIGHT_H
