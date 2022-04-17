//
// Created by Erik on 12/04/22.
//

#ifndef LII_MESHMANAGER_H
#define LII_MESHMANAGER_H
#include <memory>
#include "Mesh.h"
#include <unordered_map>
#include "ResourceManager.h"

class MeshManager : public ResourceManager
{
public:
    template<class T>
    Mesh& CreateMesh(const std::string& tag)
    {
        T* instance = new T();
        instance->SetTag(tag);
        return InsertToMap(std::unique_ptr<Mesh>(instance));
    }

    template<class T, typename ... Args>
    Mesh& CreateMesh(const std::string& tag, Args ... args)
    {
        T* instance = new T(args ...);
        instance->SetTag(tag);
        return InsertToMap(std::unique_ptr<Mesh>(instance));
    }

    Mesh* AquireMesh(const std::string& tag)
    {
        auto meshIt = meshList.find(tag);
        if(meshIt == meshList.end())
            return nullptr;
        return meshIt->second.get();
    }

    std::any GetResource(std::string tag) override
    {
        Mesh* aquiredMesh = AquireMesh(tag);
        std::any genericResource;
        genericResource.reset();
        if(aquiredMesh != nullptr)
            genericResource = aquiredMesh;
        return genericResource;
    }

    const std::string &GetTag() override
    {
        return tag;
    }

    void SetTag(const std::string &tag) override
    {
        this->tag = tag;
    }

private:
    Mesh& InsertToMap(std::unique_ptr<Mesh> mesh)
    {
        Mesh& meshRef = *mesh;

        if(mesh->GetTag().size() == 0)
            mesh->SetTag(std::to_string((long long)&meshRef));

        meshList.try_emplace(mesh->GetTag(), std::move(mesh));
        return meshRef;
    }
    std::unordered_map<std::string, std::unique_ptr<Mesh>> meshList;
    std::string tag = "mesh";
};


#endif //LII_MESHMANAGER_H
