//
// Created by Erik on 20/02/22.
//

#ifndef LII_SHAPE2DBUILDER_H
#define LII_SHAPE2DBUILDER_H
#include <memory>
#include <glm.hpp>

class Model;
class ShaderProgram;

class Shape2DBuilder
{
private:
    std::shared_ptr<glm::mat4> viewMatrix;
    std::unique_ptr<ShaderProgram> CreateDefaultShaderProgram();
public:
    std::unique_ptr<Model> CreateFillRectangle(float x, float y, float width, float height);
    std::unique_ptr<Model> CreateFillRectangle(glm::vec2 position, glm::vec2 size);
    std::unique_ptr<Model> CreateRectangle(float x, float y, float width, float height);
    std::unique_ptr<Model> CreateRectangle(glm::vec2 position, glm::vec2 size);
    std::unique_ptr<Model> CreateFillEllipse(float x, float y, float width, float height);
    std::unique_ptr<Model> CreateFillEllipse(glm::vec2 position, glm::vec2 size);
    std::unique_ptr<Model> CreateEllipse(glm::vec2 position, glm::vec2 size);
    std::unique_ptr<Model> CreateEllipse(float x, float y, float width, float height);
    std::unique_ptr<Model> CreateTriangle(glm::vec2 a1,glm::vec2 a2, glm::vec2 a3);
    std::unique_ptr<Model> CreateTriangle(std::initializer_list<glm::vec2> vertices);
    void SetViewMatrix(std::shared_ptr<glm::mat4> view);
};


#endif //LII_SHAPE2DBUILDER_H
