//
// Created by Erik on 12/04/22.
//

#include <GraphicsShader.h>
#include "GlobalResourceManager.h"
#include "DefaultShaderProgram.h"

std::unique_ptr<MeshManager> GlobalResourceManager::meshManager = std::make_unique<MeshManager>();
std::unique_ptr<TextureManager> GlobalResourceManager::textureManager = std::make_unique<TextureManager>();
std::unique_ptr<ShaderManager> GlobalResourceManager::shaderManager = std::make_unique<ShaderManager>();
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
    AddResourceManager(std::move(meshManager));
    AddResourceManager(std::move(textureManager));
    AddResourceManager(std::move(shaderManager));
}
