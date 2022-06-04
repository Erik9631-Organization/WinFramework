//
// Created by Erik on 18/02/22.
//

#ifndef LII_MESH_H
#define LII_MESH_H
#include <vector>
#include <memory>
#include "RenderObjectSubscriber.h"
#include <windows.h>
#include <glew.h>
#include "DefaultVertexAttribute.h"
#include "Taggable.h"
#include "GpuMemoryAllocator.h"
#include "ManagedPtr.hpp"
#include "GpuMemoryStrategy.h"

class Mesh : public RenderObjectSubscriber, public Taggable
{
public:
    virtual std::vector<float> * SetVertices(std::unique_ptr<std::vector<float>> vertices) = 0;
    virtual void SetVertices(std::vector<float> vertices) = 0;

    virtual std::vector<unsigned int> * SetIndexBuffer(std::unique_ptr<std::vector<unsigned int>> indices) = 0;
    virtual void SetIndexBufferContent(std::vector<unsigned int> indices) = 0;

    virtual const bool& HasIndices() = 0;
    virtual const std::vector<float> * GetVertices() const = 0 ;
    virtual const std::vector<unsigned int> * GetIndices() const = 0;
    virtual const MemManager::ManagedPtr<float, GpuMemoryStrategy> & GetGpuVerticePointer() = 0;
    virtual const MemManager::ManagedPtr<unsigned int, GpuMemoryStrategy> & GetGpuIndicePointer() = 0;

    virtual OpenGL::GpuMemoryAllocator & GetMeshManager() const = 0;
    virtual void SetPrimitiveType(const unsigned int &primitiveType) = 0;
    virtual const unsigned int & GetPrimitiveType() = 0;
    virtual ~Mesh() = default;
};

#endif //LII_MESH_H
