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
        std::unique_ptr<Model> CreateFillRectangle(glm::vec4 position, glm::vec4 size);
        std::unique_ptr<Model> CreateRectangle(float x, float y, float width, float height);
        std::unique_ptr<Model> CreateRectangle(glm::vec4 position, glm::vec4 size);
        std::unique_ptr<Model> CreateFillEllipse(float x, float y, float width, float height);
        std::unique_ptr<Model> CreateFillEllipse(glm::vec4 position, glm::vec4 size);
        std::unique_ptr<Model> CreateEllipse(glm::vec4 position, glm::vec4 size);
        std::unique_ptr<Model> CreateEllipse(float x, float y, float width, float height);
        std::unique_ptr<Model> CreateTriangle(glm::vec4 a1, glm::vec4 a2, glm::vec4 a3);
        std::unique_ptr<Model> CreateTriangle(std::initializer_list<glm::vec4> vertices);
        std::unique_ptr<Model> CreateBlock(float x, float y, float z, float width, float height, float depth);
        std::unique_ptr<Model> CreateBlock(glm::vec4 position, glm::vec4 size);
        std::unique_ptr<Model> CreateEmptyModel();
        void SetProjectionMatrix(glm::mat4 *projection);
    };
}


#endif //LII_MODELBUILDER_H
