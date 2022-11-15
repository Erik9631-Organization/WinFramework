//
// Created by erik9 on 11/15/2022.
//

#include "GdiRenderingProviderFactory.h"
#include "GdiRenderingProvider.h"

const std::string &GdiRenderingProviderFactory::GetTag()
{
    return this->tag;
}

void GdiRenderingProviderFactory::SetTag(const std::string &tag)
{
    this->tag = tag;
}

std::unique_ptr<RenderingProvider> GdiRenderingProviderFactory::Create()
{
    auto* renderingProvider = new GdiRenderingProvider();
    return std::unique_ptr<RenderingProvider>(renderingProvider);
}
