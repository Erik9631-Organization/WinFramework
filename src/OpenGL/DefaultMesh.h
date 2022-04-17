//
// Created by Erik on 18/02/22.
//

#ifndef LII_DEFAULTMESH_H
#define LII_DEFAULTMESH_H
#include "Mesh.h"
#include "MeshMemoryManager.h"

namespace OpenGL
{
    class DefaultMesh : public Mesh
    {
    public:
        DefaultMesh(int componentCount, std::vector<float> vertices);
        DefaultMesh(int componentCount, std::vector<float> vertices, std::vector<std::unique_ptr<VertexAttribute>> &attributes);
        DefaultMesh(int componentCount, const std::vector<FloatVertexAttribute>& attributes);
        std::vector<float> &SetVertices(std::unique_ptr<std::vector<float>> vertices) override;
        const std::vector<float> &GetVertices() const override;
        int GetComponentCount() override;
        ~DefaultMesh() override;
        void SetDrawMode(GLenum drawMode) override;
        std::vector<unsigned int> & SetVerticeDrawOrder(std::unique_ptr<std::vector<unsigned int>> indexOrders) override;
        const std::vector<unsigned int> & GetVerticeOrders() const override;
        void SetVertices(std::vector<float> vertices) override;
        void SetVerticeDrawOrder(std::vector<unsigned int> indexOrders) override;
        void SetTextureComponentCount(const unsigned int &componentCount) override;
        void SetComponentCount(const unsigned int &componentCount) override;
        void SetStride(const unsigned int &stride) override;
        void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
        const std::string &GetTag() override;
        void SetTag(const std::string &tag) override;
        MeshMemoryManager & GetMeshManager() const override;
        const unsigned int & GetDrawMode() override;
        const int & GetPriority() override;
    private:
        MeshMemoryManager* manager;
        void CreateDefaultAttributes();
        std::vector<std::unique_ptr<VertexAttribute>> defaultAttributes;
        void DrawArrays();
        void DrawElements();
        void Bind();
        void UnBind();
        long long id = 0;

        std::unique_ptr<std::vector<float>>vertices;
        std::unique_ptr<std::vector<unsigned int>>indexOrders;

        static const unsigned int vertexAttributeId = 0;
        static const unsigned int textureAttributeId = 1;
        static const unsigned int normalsAttributeId = 2;
        int textureComponentCount = 2;
        int normalsComponentCount = 3;
        int componentCount = 3;
        unsigned int VboId = 0; //Vertex Buffer Object
        unsigned int VaoId = 0; //Vertex Array Object
        unsigned int EboId = 0; //Element Buffer Object
        unsigned int stride = 8; //Default, 3 for vertices, 2 for texture, 3 for normals
        GLenum drawMode = GL_TRIANGLES;
        std::string tag = "";
    };
}


#endif //LII_DEFAULTMESH_H
