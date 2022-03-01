//
// Created by Erik on 20/02/22.
//

#ifndef LII_DEFAULTMODEL_H
#define LII_DEFAULTMODEL_H
#include "Model.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
class Mesh;

class DefaultModel : public Model
{
private:
    std::unique_ptr<ShaderProgram> shaderProgram;
    std::unique_ptr<Mesh> mesh;
    glm::mat4 transformMatrix{1.0f};
    std::shared_ptr<glm::mat4> viewMatrix;
public:
    DefaultModel(std::unique_ptr<ShaderProgram> shaderProgram, std::unique_ptr<Mesh> mesh);
    void Translate(const glm::vec3 &translation) override;
    void Scale(const glm::vec3 &scale) override;
    void Rotate(float angle, const glm::vec3 &axis) override;
    void SetShaderProgram(std::unique_ptr<ShaderProgram> shader) override;
    ShaderProgram &GetShader() override;
    void Draw() override;
    void ResetTransform() override;
    void SetMesh(std::unique_ptr<Mesh> mesh);
    void SetViewMatrix(std::shared_ptr<glm::mat4> view) override;
    void SetDrawMode(unsigned int drawMode) override;
};


#endif //LII_DEFAULTMODEL_H
