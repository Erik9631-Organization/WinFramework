#include "RenderObjectEventInfo.h"
#include "DirectionalLight.h"
#include "RenderingPriorities.h"
#include "CameraManager.h"
using namespace std;

//DEFINED IN THE FRAGMENT SHADER AS WELL
IdManager DirectionalLight::idManager = IdManager(maxDirectionalLights);


void DirectionalLight::SetEnabled(const bool &state)
{
    this->enabled = state;
}

const bool &DirectionalLight::GetEnabled() const
{
    return enabled;
}

void DirectionalLight::OnRender(const RenderObjectEventInfo *renderObjectEventInfo)
{
    glm::vec3 viewDirection = OpenGL::CameraManager::GetActiveCamera()->GetViewMatrix() * glm::vec4(ModeledElement::GetTranslation(), 0.0f);
    SetLight(viewDirection);
}

const int &DirectionalLight::GetPriority()
{
    return OpenGL::RenderingPriorities::Material;
}

unsigned int DirectionalLight::GetMaxDirectionalLights()
{
    return maxDirectionalLights;
}

DirectionalLight::DirectionalLight(std::unique_ptr<OpenGL::Model> model, glm::vec3 direction) : ModeledElement(std::move(model))
{
    ModeledElement::SetTranslation(direction);
    assignedId = idManager.AquireId();
    GetModel()->AddRenderObjectSubscriber(*this);
    lightColor = {0.0f, 0.0f, 0.0f, 1.0f};
}

DirectionalLight::~DirectionalLight()
{
    idManager.FreeId(assignedId);
}

void DirectionalLight::SetLight(const glm::vec3 &direction)
{
    GetModel()->GetShaderProgram().GetUniformProperties().SetProperty("directionalLights["+to_string(assignedId)+"].pos", direction);
    GetModel()->GetShaderProgram().GetUniformProperties().SetProperty("directionalLights["+to_string(assignedId)+"].enabled", (int)this->enabled);
    GetModel()->GetShaderProgram().GetUniformProperties().SetProperty("directionalLights["+to_string(assignedId)+"].color", glm::vec3{0.5f, 0.5f, 0.5f});
}

const glm::ivec4 DirectionalLight::GetColor() const
{
    return lightColor;
}

void DirectionalLight::SetColor(const glm::ivec4 &color)
{
    this->lightColor = color;
}
