//
// Created by Erik on 12/04/22.
//

#ifndef LII_GLOBALRESOURCEMANAGER_H
#define LII_GLOBALRESOURCEMANAGER_H
#include <unordered_map>
#include <any>
#include <memory>
#include "Taggable.h"
#include "ResourceManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "MeshManager.h"

class GlobalResourceManager
{
public:
    template<typename T>
    T* GetResourceManager(std::string tag)
    {
        auto managerIterator = resourceManagers.find(tag);
        if(managerIterator == resourceManagers.end())
            return nullptr;

        ResourceManager* manager = managerIterator->second.get();
        return static_cast<T*>(manager);
    }

    template<typename T>
    T* GetResource(std::string resourceManager, std::string resource)
    {
        ResourceManager* manager = GetResourceManager<ResourceManager>(resourceManager);
        if(manager == nullptr)
            return nullptr;
        std::any aquiredResource = manager->GetResource(resource);
        if(!aquiredResource.has_value())
            return nullptr;

        return std::any_cast<T*>(aquiredResource);
    }

    void SetDefaultTextureManager(std::string& managerName)
    {
        defaultTextureManager = GetResourceManager<TextureManager>(managerName);
    }

    void SetDefaultMeshManager(std::string& managerName)
    {
        defaultMeshManager = GetResourceManager<MeshManager>(managerName);
    }

    void SetDefaultModelManager(std::string& managerName)
    {
        // Not implemented yet
    }

    void SetDefaultShaderProgramManager(std::string& managerName)
    {
        defaultShaderManager = GetResourceManager<ShaderManager>(managerName);
    }

    MeshManager *GetDefaultMeshManager() const;
    TextureManager *GetDefaultTextureManager() const;
    ShaderManager *GetDefaultShaderManager() const;

    GlobalResourceManager();

    static GlobalResourceManager& GetGlobalResourceManager();
    void AddResourceManager(std::unique_ptr<ResourceManager> resourceManager);

private:
    MeshManager* defaultMeshManager;
    TextureManager* defaultTextureManager;
    ShaderManager* defaultShaderManager;

    //Singleton, has to be unique_ptr
    static std::unique_ptr<GlobalResourceManager> globalManager;
    std::unordered_map<std::string, std::unique_ptr<ResourceManager>> resourceManagers;
};


#endif //LII_GLOBALRESOURCEMANAGER_H
