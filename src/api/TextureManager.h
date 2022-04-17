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
    template<class T, typename Args>
    Texture& CreateTexture(Args args ...)
    {
        T* instance = new T();
        instance->SetTag(tag);
        return InsertToMap(std::unique_ptr<Texture>(instance));
    }

    template<class T, typename ... Args>
    Texture& CreateTexture(const std::string& tag, Args ... args)
    {
        T* instance = new T(args ...);
        instance->SetTag(tag);
        return InsertToMap(std::unique_ptr<Texture>(instance));
    }

    Texture* AquireTextre(const std::string& tag)
    {
        auto textureIt = textureList.find(tag);
        if(textureIt == textureList.end())
            return nullptr;
        return textureIt->second.get();
    }

    std::any GetResource(std::string tag) override
    {
        Texture* aquiredTexture = AquireTextre(tag);
        std::any genericResource;
        genericResource.reset();
        if(aquiredTexture != nullptr)
            genericResource = aquiredTexture;
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
