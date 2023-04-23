//
// Created by Erik on 15/02/22.
//

#ifndef LII_SHADERPROGRAM_H
#define LII_SHADERPROGRAM_H
#include <memory>
#include "Uniform.h"
#include "Shader.h"
#include "Identifiable.h"
#include "Taggable.h"
#include "Resource.h"

class Shader;

class ShaderProgram : public OpenGL::Uniform, public Identifiable, public Resource
{
public:
    virtual OpenGL::Shader& AssembleShader(std::unique_ptr<OpenGL::Shader> shader) = 0;
    virtual OpenGL::Shader& GetShader(int id) = 0;
    virtual bool HasShader(int id) = 0;
    virtual std::unique_ptr<OpenGL::Shader>RemoveShader(int id) = 0;
    virtual bool Link() = 0;
    virtual ~ShaderProgram() = default;
};

#endif //LII_SHADERPROGRAM_H
