//
// Created by erik9 on 11/15/2022.
//

#ifndef LII_RENDERINGPROVIDERMANAGER_H
#define LII_RENDERINGPROVIDERMANAGER_H
#include <memory>
#include "RenderingProvider.h"
#include "Factory.h"
#include <string>
#include <unordered_map>

class RenderingProviderManager
{
private:
    static std::unique_ptr<RenderingProviderManager> renderingProviderManager;
    std::string defaultRenderingManager = "GdiRenderingProvider";
public:
    RenderingProviderManager();
    std::unique_ptr<RenderingProvider> Create(const std::string& tag);
    std::unique_ptr<RenderingProvider> Create();
    std::unordered_map<std::string, std::unique_ptr<Factory<RenderingProvider>>> renderingProviderFactories;
    void RegisterRenderingProviderFactory(std::unique_ptr<Factory<RenderingProvider>> renderingProviderFactory);
    void UnRegisterRenderingProviderFactory(const std::string &tag);
    void SetDefaultRenderingProvider(const std::string &tag);
    static RenderingProviderManager* GetRenderingProviderManager();
};


#endif //LII_RENDERINGPROVIDERMANAGER_H
