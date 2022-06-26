//
// Created by Erik on 26/06/22.
//

#include "PointLight.h"
#include "ModelBuilder.h"
#include "RenderEventInfo.h"
#include "RenderingPriorities.h"
PointLight** PointLight::lightPool = GenerateLightPool();

unique_ptr<PointLight> PointLight::Create(std::unique_ptr<OpenGL::Model> model)
{
    unsigned int id = AquireId();
    if(id == -1)
        return nullptr;
    auto* lightInstance = new PointLight(std::move(model), 0);
    lightInstance->SetEnabled(true);


    return std::unique_ptr<PointLight>(lightInstance);
}

int PointLight::AquireId()
{
    for(unsigned int i = 0; i < maxLights; i++)
        if(lightPool[i] == nullptr)
            return i;
    return -1;
}

PointLight::PointLight(std::unique_ptr<OpenGL::Model> model, const unsigned int &id) :
    ModeledElement(std::move(model))
{
    SetId(id);
    model->AddRenderObjectSubscriber(*this);
}

PointLight::~PointLight()
{
    FreeLight(lightId);
    model->RemoveRenderObjectSubscriber(*this);
}

void PointLight::FreeLight(const unsigned int& id)
{
    lightPool[id] = nullptr;
}

void PointLight::SetId(unsigned int id)
{
    this->lightId = id;
    lightPositionUniform = "lightPositions["+std::to_string(id)+"]";
    usedLightsUniform = "usedLights["+std::to_string(id)+"]";
}

void PointLight::UpdateShader()
{
    GetModel()->GetShaderProgram().GetUniformProperties().SetProperty(lightPositionUniform, GetTranslation());
    GetModel()->GetShaderProgram().GetUniformProperties().SetProperty(usedLightsUniform, (int)enabled);
}
void PointLight::SetEnabled(const bool &state)
{
    enabled = state;
}

const bool & PointLight::GetEnabled()
{
    return enabled;
}

void PointLight::OnRender(const RenderObjectEventInfo *renderObjectEventInfo)
{
    UpdateShader();
}

const int &PointLight::GetPriority()
{
    return OpenGL::RenderingPriorities::Material;
}

PointLight **PointLight::GenerateLightPool()
{
    PointLight** pool = new PointLight*[maxLights];
    memset(pool, 0, sizeof(PointLight*)*maxLights);
    return pool;
}
