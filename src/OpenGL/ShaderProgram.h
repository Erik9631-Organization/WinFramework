//
// Created by Erik on 15/02/22.
//

#ifndef LII_SHADERPROGRAM_H
#define LII_SHADERPROGRAM_H
#include <memory>
#include "Uniform.h"
class Shader;

class ShaderProgram : public Uniform
{
public:
    virtual Shader& AddShader(std::unique_ptr<Shader> shader) = 0;
    virtual Shader& GetShader(int id) = 0;
    virtual bool HasShader(int id) = 0;
    virtual std::unique_ptr<Shader>RemoveShader(int id) = 0;
    virtual unsigned int GetId() = 0;
    virtual bool Link() = 0;
    virtual void Use() = 0;
    virtual ~ShaderProgram() = default;
};


#endif //LII_SHADERPROGRAM_H
