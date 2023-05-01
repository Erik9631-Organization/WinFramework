//
// Created by erik9 on 11/15/2022.
//

#include "OpenGLRenderingProviderFactory.h"
#include "OpenGLRenderer.h"
#include <memory>

std::unique_ptr<Renderer> OpenGLRenderingProviderFactory::Create()
{
    auto* openGLRenderingProvider = new OpenGLRenderer();
    return std::unique_ptr<Renderer>(openGLRenderingProvider);
}

const std::string &OpenGLRenderingProviderFactory::GetTag()
{
    return tag;
}

void OpenGLRenderingProviderFactory::SetTag(const std::string &tag)
{
    this->tag = tag;
}

std::unique_ptr<Renderer> OpenGLRenderingProviderFactory::Create(std::any args)
{
    return Create();
}
