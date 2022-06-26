//
// Created by Erik on 26/06/22.
//

#ifndef LII_POINTLIGHT_H
#define LII_POINTLIGHT_H
#include "ModeledElement.h"
#include "Light.h"
#include "RenderObjectSubscriber.h"

class PointLight : public ModeledElement, public Light, public RenderObjectSubscriber
{
public:
    static unique_ptr<PointLight> Create(std::unique_ptr<OpenGL::Model> model);
    ~PointLight();
    void SetEnabled(const bool &State) override;
    const bool & GetEnabled() override;
    void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
    const int &GetPriority() override;
private:
    bool enabled = true;
    void UpdateShader();
    std::string lightPositionUniform = "";
    std::string usedLightsUniform = "";
    void SetId(unsigned int id);
    PointLight(std::unique_ptr<OpenGL::Model> model, const unsigned int &id);
    unsigned int lightId = 0;
    static constexpr unsigned int maxLights = 100;
    static int AquireId();
    static void FreeLight(const unsigned int& id);
    static PointLight** lightPool;
    static PointLight** GenerateLightPool();
};


#endif //LII_POINTLIGHT_H
