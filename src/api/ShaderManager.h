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

	ShaderProgram* AquireShaderProgram(const std::string& tag)
	{
		auto shaderProgramIt = shaderProgramList.find(tag);
		if (shaderProgramIt == shaderProgramList.end())
			return nullptr;
		return shaderProgramIt->second.get();
	}

    std::any GetResource(std::string tag) override
    {
        ShaderProgram* aquiredShaderProgram = AquireShaderProgram(tag);
        std::any genericResource;
        genericResource.reset();
        if(aquiredShaderProgram != nullptr)
            genericResource = aquiredShaderProgram;
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
