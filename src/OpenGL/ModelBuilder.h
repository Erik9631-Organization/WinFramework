//
// Created by Erik on 20/02/22.
//

#ifndef LII_MODELBUILDER_H
#define LII_MODELBUILDER_H
#include <memory>
#include <glm.hpp>
#include "ShaderProgram.h"
#include "Model.h"


class ShaderProgram;
class MeshManager;

namespace OpenGL
{
    class Model;
    class ModelBuilder
    {
    private:
        glm::mat4* projectionMatrix;
        ShaderProgram* shaderProgram = nullptr;
        MeshManager* meshManager = nullptr;
    public:
        ModelBuilder();
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
        std::unique_ptr<Model> CreateBlock(float x, float y, float z, float width, float height, float depth);
        std::unique_ptr<Model> CreateBlock(glm::vec3 position, glm::vec3 size);
        void SetProjectionMatrix(glm::mat4 *projection);
    };
}


#endif //LII_MODELBUILDER_H
