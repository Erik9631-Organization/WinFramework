//
// Created by Erik on 18/02/22.
//

#ifndef LII_MESH_H
#define LII_MESH_H
#include <vector>
#include <memory>
#include "Renderable.h"
#include <windows.h>
#include <glew.h>
class Mesh
{
public:
    virtual std::vector<float>& SetVertices(std::unique_ptr<std::vector<float>> vertices) = 0;
    virtual void SetVertices(std::vector<float> vertices) = 0;

    virtual std::vector<unsigned int> & SetVerticeDrawOrder(std::unique_ptr<std::vector<unsigned int>> indexOrders) = 0;
    virtual void SetVerticeDrawOrder(std::vector<unsigned int> indexOrders) = 0;

    virtual const std::vector<float>& GetVertices() = 0;
    virtual const std::vector<unsigned int> & GetVerticeOrders() = 0;

    virtual int GetComponentCount() = 0;
    virtual void Draw() = 0;
    virtual void DrawMode(GLenum drawMode) = 0;
    virtual ~Mesh() = default;
};

#endif //LII_MESH_H
