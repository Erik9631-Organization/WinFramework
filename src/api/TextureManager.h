//
// Created by Erik on 12/04/22.
//

#ifndef LII_TEXTUREMANAGER_H
#define LII_TEXTUREMANAGER_H
#include <memory>
#include "Texture.h"
#include <unordered_map>
#include "ResourceManager.h"

class TextureManager : public ResourceManager
{

public:
    template<class T, typename ... Args>
    Texture& CreateTexture(const std::string& tag, Args ... args)
    {
        T* instance = new T(args ...);
        instance->SetTag(tag);
        return InsertToMap(std::unique_ptr<Texture>(instance));
    }

    Texture* GetTexture(const std::string& tag)
    {
        auto textureIt = textureList.find(tag);
        if(textureIt == textureList.end())
            return nullptr;
        return textureIt->second.get();
    }

    Resource * GetResource(std::string tag) override
    {
        return GetTexture(tag);;
    }

    std::unique_ptr<std::vector<Resource *>> GetLoadedResources() override
    {
        std::unique_ptr<std::vector<Resource*>> resourceList = std::make_unique<std::vector<Resource*>>();
        for(auto& mesh : textureList)
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
        for(auto& mesh : textureList)
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
        for(auto& mesh : textureList)
        {
            auto& meshPtr = mesh.second;
            if(!meshPtr->IsLoaded())
                resourceList->push_back(meshPtr.get());
        }
        return resourceList;
    }

    const std::string &GetTag() override
    {
        return tag;
    }

    void SetTag(const std::string &tag) override
    {
        this->tag = tag;
    }

    void LoadResource(const string &resource) override
    {
        auto* resourceToLoad = GetResource(resource);
        if(resourceToLoad == nullptr)
            return;
        resourceToLoad->Load();
    }

    void UnloadResource(const string &resource) override
    {
        auto* resourceToLoad = GetResource(resource);
        if(resourceToLoad == nullptr)
            return;
        resourceToLoad->Unload();
    }


private:
    Texture& InsertToMap(std::unique_ptr<Texture> texture)
    {
        Texture& textureRef = *texture;

        texture->LoadFromFile();
        if(texture->GetTag().size() == 0)
            texture->SetTag(texture->GetPath());

        textureList.try_emplace(texture->GetTag(), std::move(texture));
        return textureRef;
    }
    std::unordered_map<std::string, std::unique_ptr<Texture>> textureList;
    std::string tag = "texture";
};


#endif //LII_TEXTUREMANAGER_H
