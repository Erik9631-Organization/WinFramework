//
// Created by Erik on 10/04/22.
//

#ifndef LII_MATERIAL_H
#define LII_MATERIAL_H
#include "glm.hpp"
#include "RenderObjectSubscriber.h"
#include "DefaultShaderProgram.h"
#include "Clonable.h"
#include "ShaderProgram.h"

namespace OpenGL
{
    class Material : public RenderObjectSubscriber
    {
    private:
        //Can be null
        ShaderProgram& program;
        glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f);;
        glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        float specularStrength = 8;
    public:
        Material(ShaderProgram &program);
        void SetAmbient(const glm::vec3& ambient);
        void SetSpecular(const glm::vec3& specular);
        void SetDiffuse(const glm::vec3& diffuse);
        void SetSpecularStrength(const float& specularStrength);
        void SetColor(const glm::vec4& color);
        void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
        const int & GetPriority() override;
    };

}


#endif //LII_MATERIAL_H
