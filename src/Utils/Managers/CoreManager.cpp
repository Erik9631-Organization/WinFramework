//
// Created by erik9 on 11/16/2022.
//

#include "CoreManager.h"
std::unique_ptr<CoreManager> CoreManager::renderingProviderManager = std::make_unique<CoreManager>();

CoreManager::CoreManager()
{

}

std::unique_ptr<Core> CoreManager::Create(const std::string &tag)
{
    auto it = renderingProviderFactories.find(tag);
    if(it == renderingProviderFactories.end())
        return nullptr;
    return it->second->Create();
}

std::unique_ptr<Core> CoreManager::Create()
{
    return Create(defaultCoreFactory);
}

CoreManager *CoreManager::GetRenderingProviderManager()
{
    return renderingProviderManager.get();
}

void CoreManager::RegisterRenderingProviderFactory(std::unique_ptr<Factory<Core>> coreFactory)
{
    renderingProviderFactories.try_emplace(coreFactory->GetTag(), std::move(coreFactory));
}

void CoreManager::UnRegisterRenderingProviderFactory(const std::string &tag)
{
    auto it = renderingProviderFactories.find(tag);
    if(it == renderingProviderFactories.end())
        return;
    renderingProviderFactories.erase(it);
}

void CoreManager::SetDefaultRenderingProvider(const std::string &tag)
{
    defaultCoreFactory = tag;
}
