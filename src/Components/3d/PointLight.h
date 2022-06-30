//
// Created by Erik on 26/06/22.
//

#ifndef LII_POINTLIGHT_H
#define LII_POINTLIGHT_H
#include "ModeledElement.h"
#include "Light.h"
#include "RenderObjectSubscriber.h"
#include <IdManager.h>

class PointLight : public ModeledElement, public Light, public RenderObjectSubscriber
{
public:
    PointLight(std::unique_ptr<OpenGL::Model> model);
    ~PointLight();
    void SetEnabled(const bool &State) override;
    const bool & GetEnabled() const override;
    void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
    const int &GetPriority() override;
    const glm::vec4 GetColor() const override;
    void SetColor(const glm::vec4 &color) override;
private:
    glm::vec4 color;
    static IdManager idManager;
    bool enabled = true;
    void UpdateShader();
    unsigned int lightId = 0;
    static constexpr unsigned int maxLights = 20;
};


#endif //LII_POINTLIGHT_H
