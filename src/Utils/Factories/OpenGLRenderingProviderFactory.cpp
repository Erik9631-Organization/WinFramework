//
// Created by erik9 on 11/15/2022.
//

#include "OpenGLRenderingProviderFactory.h"
#include "OpenGLRenderingProvider.h"
#include <memory>

std::unique_ptr<RenderingProvider> OpenGLRenderingProviderFactory::Create()
{
    auto* openGLRenderingProvider = new OpenGLRenderingProvider();
    return std::unique_ptr<RenderingProvider>(openGLRenderingProvider);
}

const std::string &OpenGLRenderingProviderFactory::GetTag()
{
    return tag;
}

void OpenGLRenderingProviderFactory::SetTag(const std::string &tag)
{
    this->tag = tag;
}

std::unique_ptr<RenderingProvider> OpenGLRenderingProviderFactory::Create(std::any args)
{
    return Create();
}
