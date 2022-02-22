//
// Created by Erik on 20/02/22.
//

#ifndef LII_MODEL_H
#define LII_MODEL_H
#include <memory>
#include <glm.hpp>
class Vector3;
class ShaderProgram;

class Model
{
public:
    virtual void Translate(const glm::vec3 &position) = 0;
    virtual void Scale(const glm::vec3 &position) = 0;
    virtual void Rotate(float angle, const glm::vec3 &axis) = 0;
    virtual void SetShaderProgram(std::unique_ptr<ShaderProgram> shader) = 0;
    virtual void ResetTransform() = 0;
    virtual ShaderProgram & GetShader() = 0;
    virtual void Draw() = 0;
    virtual void SetViewMatrix(std::shared_ptr<glm::mat4> view) = 0;
};


#endif //LII_MODEL_H
