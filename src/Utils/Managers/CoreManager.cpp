//
// Created by erik9 on 11/16/2022.
//

#include "CoreManager.h"
#include "CoreFactory.h"


std::unique_ptr<CoreManager> CoreManager::coreManager = std::make_unique<CoreManager>();

std::unique_ptr<Core> CoreManager::Create(const std::string &tag, std::optional<std::any> args = std::nullopt)
{
    auto it = coreFactories.find(tag);
    if(it == coreFactories.end())
        return nullptr;
    std::unique_ptr<Core> corePtr;
    if(args->has_value())
        corePtr = it->second->Create(args.value());
    else
        corePtr = it->second->Create();
    return corePtr;
}

std::unique_ptr<Core> CoreManager::Create(std::optional<std::any> args)
{
    return Create(defaultCoreFactory, std::move(args));
}


CoreManager *CoreManager::GetCoreManager()
{
    return coreManager.get();
}

void CoreManager::RegisterCoreFactory(std::unique_ptr<Factory<Core>> coreFactory)
{
    coreFactories.try_emplace(coreFactory->GetTag(), std::move(coreFactory));
}

void CoreManager::UnRegisterCoreFactory(const std::string &tag)
{
    auto it = coreFactories.find(tag);
    if(it == coreFactories.end())
        return;
    coreFactories.erase(it);
}

void CoreManager::SetDefaultCoreFactory(const std::string &tag)
{
    defaultCoreFactory = tag;
}

CoreManager::CoreManager()
{
    RegisterCoreFactory(std::make_unique<CoreFactory>());
}

