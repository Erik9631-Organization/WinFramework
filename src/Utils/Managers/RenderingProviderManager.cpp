//
// Created by erik9 on 11/15/2022.
//

#include "RenderingProviderManager.h"
#ifdef windows
#include "GdiRenderingProviderFactory.h"
#include "OpenGLRenderingProviderFactory.h"
#endif

std::unique_ptr<RenderingProviderManager> RenderingProviderManager::renderingProviderManager = std::make_unique<RenderingProviderManager>();

std::unique_ptr<RenderingProvider> RenderingProviderManager::Create(const std::string& tag)
{
    auto iter = renderingProviderFactories.find(tag);
    if (iter == renderingProviderFactories.end())
        return nullptr;
    return iter->second->Create();
}

void RenderingProviderManager::RegisterRenderingProviderFactory(std::unique_ptr<Factory<RenderingProvider>> renderingProviderFactory)
{
    renderingProviderFactories.try_emplace(renderingProviderFactory->GetTag(), std::move(renderingProviderFactory));
}

void RenderingProviderManager::UnRegisterRenderingProviderFactory(const std::string &tag)
{
    auto iter = renderingProviderFactories.find(tag);
    if (iter == renderingProviderFactories.end())
        return;
    renderingProviderFactories.erase(iter);
}

RenderingProviderManager::RenderingProviderManager()
{
#ifdef windows
    auto gdiRenderingProviderFactory = std::make_unique<GdiRenderingProviderFactory>();
    RegisterRenderingProviderFactory(std::move(gdiRenderingProviderFactory));

    auto openGLRenderingProviderFactory = std::make_unique<OpenGLRenderingProviderFactory>();
    RegisterRenderingProviderFactory(std::move(openGLRenderingProviderFactory));
#endif
}

std::unique_ptr<RenderingProvider> RenderingProviderManager::Create()
{
    if (defaultRenderingManager.empty())
        return nullptr;
    return Create(defaultRenderingManager);
}

void RenderingProviderManager::SetDefaultRenderingProvider(const std::string &tag)
{
    defaultRenderingManager = tag;
}

RenderingProviderManager *RenderingProviderManager::GetRenderingProviderManager()
{
    return renderingProviderManager.get();
}
