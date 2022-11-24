//
// Created by erik9 on 11/15/2022.
//

#include "WindowBuilder.h"

const std::string &WindowBuilder::getRenderingBackend() const
{
    return renderingBackend;
}

void WindowBuilder::setRenderingBackend(const std::string &renderingBackend)
{
    WindowBuilder::renderingBackend = renderingBackend;
}
