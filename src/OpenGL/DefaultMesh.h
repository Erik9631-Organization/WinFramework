//
// Created by Erik on 18/02/22.
//

#ifndef LII_DEFAULTMESH_H
#define LII_DEFAULTMESH_H
#include "Mesh.h"

class DefaultMesh : public Mesh
{
public:
    DefaultMesh(int componentCount, std::vector<float> vertices);
    DefaultMesh(int componentCount);
    std::vector<float> &SetVertices(std::unique_ptr<std::vector<float>> vertices) override;
    const std::vector<float> &GetVertices() override;
    int GetComponentCount() override;
    ~DefaultMesh() override;
    void Draw() override;
    void DrawMode(GLenum drawMode) override;
    std::vector<unsigned int> & SetVerticeDrawOrder(std::unique_ptr<std::vector<unsigned int>> indexOrders) override;
    const std::vector<unsigned int> & GetVerticeOrders() override;
    void SetVertices(std::vector<float> vertices) override;
    void SetVerticeDrawOrder(std::vector<unsigned int> indexOrders) override;
private:
    void DrawArrays();
    void DrawElements();
    void Bind();
    void UnBind();

    std::unique_ptr<std::vector<float>>vertices;
    std::unique_ptr<std::vector<unsigned int>>indexOrders;

    int componentCount = 3;
    unsigned int VboId = 0; //Vertex Buffer Object
    unsigned int VaoId = 0; //Vertex Array Object
    unsigned int EboId = 0; //Element Buffer Object
    GLenum drawMode = GL_TRIANGLES;
};


#endif //LII_DEFAULTMESH_H
