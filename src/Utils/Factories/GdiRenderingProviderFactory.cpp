//
// Created by erik9 on 11/15/2022.
//

#include "GdiRenderingProviderFactory.h"
#include "GdiRenderer.h"

const std::string &GdiRenderingProviderFactory::GetTag()
{
    return this->tag;
}

void GdiRenderingProviderFactory::SetTag(const std::string &tag)
{
    this->tag = tag;
}

std::unique_ptr<Renderer> GdiRenderingProviderFactory::Create()
{
    auto* renderingProvider = new GdiRenderer();
    return std::unique_ptr<Renderer>(renderingProvider);
}

std::unique_ptr<Renderer> GdiRenderingProviderFactory::Create(std::any args)
{
    return Create();
}
