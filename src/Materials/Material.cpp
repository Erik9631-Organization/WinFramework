//
// Created by Erik on 10/04/22.
//

#include "Material.h"
#include "ShaderProgram.h"
#include "RenderingPriorities.h"

using namespace OpenGL;
//Called by the rendering manager. The shaders are set by the manager. Only properties are to be set here.
void Material::OnRender(const RenderObjectEventInfo *renderObjectEventInfo)
{
    program.GetUniformProperties().SetProperty("material.ambientStrength", ambient);
    program.GetUniformProperties().SetProperty("material.specular", specular);
    program.GetUniformProperties().SetProperty("material.diffuse", diffuse);
    program.GetUniformProperties().SetProperty("material.specStrength", specularStrength);
    program.GetUniformProperties().SetProperty("color", color);
}

void Material::SetSpecularStrength(const float &specularStrength)
{
    this->specularStrength = specularStrength;
}

void Material::SetDiffuse(const glm::vec3 &diffuse)
{
    this->diffuse = diffuse;
}

void Material::SetSpecular(const glm::vec3 &specular)
{
    this->specular = specular;
}

void Material::SetAmbient(const glm::vec3 &ambient)
{
    this->ambient = ambient;
}

Material::Material(ShaderProgram &program) : program(program)
{

}

void Material::SetColor(const glm::vec4& color)
{
    this->color = color;
}

const int & Material::GetPriority()
{
    return RenderingPriorities::Material;
}
