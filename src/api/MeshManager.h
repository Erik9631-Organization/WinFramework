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

    Mesh* GetMesh(const std::string& tag)
    {
        auto meshIt = meshList.find(tag);
        if(meshIt == meshList.end())
            return nullptr;
        return meshIt->second.get();
    }

    Resource * GetResource(std::string tag) override
    {
        return GetMesh(tag);
    }

    const std::string &GetTag() override
    {
        return tag;
    }

    void SetTag(const std::string &tag) override
    {
        this->tag = tag;
    }

    std::unique_ptr<std::vector<Resource *>> GetLoadedResources() override
    {
        std::unique_ptr<std::vector<Resource*>> resourceList = std::make_unique<std::vector<Resource*>>();
        for(auto& mesh : meshList)
        {
            auto& meshPtr = mesh.second;
            if(meshPtr->IsLoaded())
                resourceList->push_back(meshPtr.get());
        }
        return resourceList;
    }

    std::unique_ptr<std::vector<Resource *>> GetUnloadedResources() override
    {
        std::unique_ptr<std::vector<Resource*>> resourceList = std::make_unique<std::vector<Resource*>>();
        for(auto& mesh : meshList)
        {
            auto& meshPtr = mesh.second;
            if(!meshPtr->IsLoaded())
                resourceList->push_back(meshPtr.get());
        }
        return resourceList;
    }

    std::unique_ptr<std::vector<Resource *>> GetResources() override
    {
        std::unique_ptr<std::vector<Resource*>> resourceList = std::make_unique<std::vector<Resource*>>();
        for(auto& mesh : meshList)
        {
            auto& meshPtr = mesh.second;
            if(!meshPtr->IsLoaded())
                resourceList->push_back(meshPtr.get());
        }
        return resourceList;
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

    Mesh& InsertToMap(std::unique_ptr<Mesh> mesh, std::string tag)
    {
        mesh->SetTag(tag);
        InsertToMap(std::move(mesh));
    }


    std::unordered_map<std::string, std::unique_ptr<Mesh>> meshList;
    std::string tag = "mesh";
};


#endif //LII_MESHMANAGER_H
