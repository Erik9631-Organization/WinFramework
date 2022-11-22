//
// Created by Erik on 12/04/22.
//

#ifndef LII_SHADERMANAGER_H
#define LII_SHADERMANAGER_H
#include "ShaderProgram.h"
#include <memory>
#include <unordered_map>
#include "ResourceManager.h"
#include "DefaultShaderProgram.h"
using namespace std;

class ShaderManager : public ResourceManager
{
public:
    template<class T>
    ShaderProgram& CreateShaderProgram(const std::string& tag)
    {
        T* instance = new T();
        instance->SetTag(tag);
        return InsertToMap(std::move(std::unique_ptr<ShaderProgram>(instance)));
    }
	template<class T, typename ... Args>
	ShaderProgram& CreateShaderProgram(const std::string& tag, Args ... args)
	{
        T* instance = new T(args ...);
        instance->SetTag(tag);
        return InsertToMap(std::move(std::unique_ptr<ShaderProgram>(instance)));
	}

	ShaderProgram* GetShaderProgram(const std::string& tag)
	{
		auto shaderProgramIt = shaderProgramList.find(tag);
		if (shaderProgramIt == shaderProgramList.end())
			return nullptr;
		return shaderProgramIt->second.get();
	}

    Resource * GetResource(std::string tag) override
    {
        return GetShaderProgram(tag);;
    }

    std::unique_ptr<std::vector<Resource *>> GetLoadedResources() override
    {
        std::unique_ptr<std::vector<Resource*>> resourceList = std::make_unique<std::vector<Resource*>>();
        for(auto& mesh : shaderProgramList)
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
        for(auto& mesh : shaderProgramList)
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
        for(auto& mesh : shaderProgramList)
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

    bool ResourceExists(const string &resourceTag) override
    {
        if(GetResource(resourceTag) == nullptr)
            return false;
        return true;
    }

private:
    ShaderProgram& InsertToMap(std::unique_ptr<ShaderProgram> shaderProgram)
    {
        ShaderProgram& shaderProgramRef = *shaderProgram;

        if (shaderProgramRef.GetTag().size() == 0)
            shaderProgramRef.SetTag(std::to_string((long long)&shaderProgramRef));

        shaderProgramList.try_emplace(shaderProgramRef.GetTag(), std::move(shaderProgram));
        return shaderProgramRef;
    }
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> shaderProgramList;
    std::string tag = "shader";
};



#endif //LII_SHADERMANAGER_H
