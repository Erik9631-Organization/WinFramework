//
// Created by erik9 on 11/16/2022.
//

#ifndef LII_COREMANAGER_H
#define LII_COREMANAGER_H
#include <memory>
#include <string>
#include <unordered_map>
#include "Factory.h"

class CoreManager
{
private:
    static std::unique_ptr<CoreManager> renderingProviderManager;
    std::string defaultCoreFactory = "WindowsCore";
public:
    CoreManager();
    std::unique_ptr<Core> Create(const std::string& tag);
    std::unique_ptr<Core> Create();
    std::unordered_map<std::string, std::unique_ptr<Factory<Core>>> renderingProviderFactories;
    void RegisterRenderingProviderFactory(std::unique_ptr<Factory<Core>> coreFactory);
    void UnRegisterRenderingProviderFactory(const std::string &tag);
    void SetDefaultRenderingProvider(const std::string &tag);
    static CoreManager* GetRenderingProviderManager();
};


#endif //LII_COREMANAGER_H
