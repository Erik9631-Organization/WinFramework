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
#include "FloatVertexAttribute.h"
#include "Taggable.h"
#include "MeshMemoryManager.h"
#include "ManagedPtr.hpp"
#include "GpuMemoryStrategy.h"

class Mesh : public RenderObjectSubscriber, public Taggable
{
public:
    virtual std::vector<float>& SetVertices(std::unique_ptr<std::vector<float>> vertices) = 0;
    virtual void SetVertices(std::vector<float> vertices) = 0;

    virtual std::vector<unsigned int> & SetVerticeDrawOrder(std::unique_ptr<std::vector<unsigned int>> indexOrders) = 0;
    virtual void SetVerticeDrawOrder(std::vector<unsigned int> indexOrders) = 0;

    virtual const std::vector<float>& GetVertices() const = 0 ;
    virtual const std::vector<unsigned int> & GetVerticeOrders() const = 0;
    virtual void SetGpuPointer(MemManager::ManagedPtr<float, GpuMemoryStrategy> ptr) = 0;
    virtual const MemManager::ManagedPtr<float, GpuMemoryStrategy> & GetGpuPointer() = 0;

    virtual void SetTextureComponentCount(const unsigned int& componentCount) = 0;
    virtual void SetComponentCount(const unsigned int& componentCount) = 0;
    virtual void SetStride(const unsigned  int& stride) = 0;
    virtual OpenGL::MeshMemoryManager & GetMeshManager() const = 0;
    virtual int GetComponentCount() = 0;
    virtual void SetDrawMode(GLenum drawMode) = 0;
    virtual const unsigned int & GetDrawMode() = 0;
    virtual ~Mesh() = default;
};

#endif //LII_MESH_H
