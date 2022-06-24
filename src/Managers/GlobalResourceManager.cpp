//
// Created by Erik on 12/04/22.
//

#include <GraphicsShader.h>
#include "GlobalResourceManager.h"
#include "DefaultShaderProgram.h"

std::unique_ptr<GlobalResourceManager> GlobalResourceManager::globalManager = std::make_unique<GlobalResourceManager>();

void GlobalResourceManager::AddResourceManager(std::unique_ptr<ResourceManager> resourceManager)
{
    resourceManagers.try_emplace(resourceManager->GetTag(), std::move(resourceManager));
}

GlobalResourceManager &GlobalResourceManager::GetGlobalResourceManager()
{
    return *globalManager;
}

GlobalResourceManager::GlobalResourceManager()
{
    AddResourceManager(std::move(std::make_unique<MeshManager>()));
    AddResourceManager(std::move(std::make_unique<TextureManager>()));
    AddResourceManager(std::move(std::make_unique<ShaderManager>()));

    //Get the defaults
    defaultMeshManager = GetResourceManager<MeshManager>("mesh");
    defaultTextureManager = GetResourceManager<TextureManager>("texture");
    defaultShaderManager = GetResourceManager<ShaderManager>("shader");

}
