//
// Created by Erik on 26/06/22.
//

#include "PointLight.h"
#include "ModelBuilder.h"
#include "RenderEventInfo.h"
#include "RenderingPriorities.h"
using namespace std;

IdManager PointLight::idManager = IdManager(maxLights);

PointLight::PointLight(std::unique_ptr<OpenGL::Model> model) :
    ModeledElement(std::move(model))
{
    this->lightId = idManager.AquireId();
    GetModel()->AddRenderObjectSubscriber(*this);
    this->color = {0.5f, 0.5f, 0.5f, 1.0f};
}

PointLight::~PointLight()
{
    model->RemoveRenderObjectSubscriber(*this);
    idManager.FreeId(lightId);
}

void PointLight::UpdateShader()
{
    std::string colorStr = "pointLights["+to_string(lightId)+"]."+"color";
    std::string positionStr = "pointLights["+to_string(lightId)+"]."+"pos";
    std::string enabledStr = "pointLights["+to_string(lightId)+"]."+"enabled";

    glm::vec3 viewLight = GetModel()->GetCamera()->GetViewMatrix() * glm::vec4(ModeledElement::GetTranslation(), 1.0f);

    GetModel()->GetShaderProgram().GetUniformProperties().SetProperty(colorStr, glm::vec3{color});
    GetModel()->GetShaderProgram().GetUniformProperties().SetProperty(positionStr, viewLight);
    GetModel()->GetShaderProgram().GetUniformProperties().SetProperty(enabledStr, (int)enabled);

}
void PointLight::SetEnabled(const bool &state)
{
    enabled = state;
}

const bool & PointLight::GetEnabled() const
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


const glm::ivec4 PointLight::GetColor() const
{
    return glm::ivec4();
}

void PointLight::SetColor(const glm::ivec4 &color)
{
    this->color = color;
}
