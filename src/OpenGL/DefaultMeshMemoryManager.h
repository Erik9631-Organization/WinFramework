//
// Created by Erik on 26/03/22.
//

#ifndef LII_DEFAULTMESHMEMORYMANAGER_H
#define LII_DEFAULTMESHMEMORYMANAGER_H
#include <vector>
#include <unordered_map>
#include <string>
#include "FloatVertexAttribute.h"
#include <memory>
#include "MeshMemoryManager.h"
#include "VboProperties.h"


class Mesh;
namespace OpenGL
{
    class DefaultMeshMemoryManager : public MeshMemoryManager
    {
    private:
        struct MeshMetaData
        {
            Mesh* mesh;
            long long unsigned int meshOffset;
            long long unsigned int meshSize;

            bool hasEbo = false;
            long long unsigned int orderOffset;
            long long unsigned int orderSize;
        };
        //After the attributes are created, we only need to keep the has
        size_t hash;
        GLenum usage = GL_STATIC_DRAW;
        std::unique_ptr<VboProperties> vertexAttributes;

        unsigned int vboSize = 0;
        unsigned int vboExtentionSize = 0;
        unsigned int vboUsedSize = 0;

        unsigned int eboSize = 0;
        unsigned int eboUsedSize = 0;
        unsigned int eboExtentionSize = 0;


        unsigned int vboId = 0;
        unsigned int vaoId = 0;
        unsigned int eboId = 0;
        std::unordered_map<size_t, std::unique_ptr<MeshMetaData>> meshMetaData;

        void ReallocGpuBuffer(const unsigned int &newSize, unsigned int &bufferId,
                              const GLenum bufferType, unsigned int &bufferSize);
    public:
        DefaultMeshMemoryManager(std::unique_ptr<VboProperties> properties, const unsigned int &vboSize,
                                 const unsigned int &eboSize);
        void Push(Mesh &mesh);
        void PushOrder(const Mesh &mesh);
        const size_t & GetHash() const override;
        void Bind() const override;
        void UnBind() const override;
        const unsigned long long int & GetId() const override;
        void OnRender(const RenderObjectEventInfo *renderObjectEventInfo) override;
        const int & GetPriority() override;
    };
}


#endif //LII_DEFAULTMESHMEMORYMANAGER_H
