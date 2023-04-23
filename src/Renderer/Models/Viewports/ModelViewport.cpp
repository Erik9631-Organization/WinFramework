//
// Created by erik9 on 1/17/2023.
//

#include "ModelViewport.h"

bool ModelViewport::IsSet() const
{
    return isSet;
}

void ModelViewport::ResetViewport()
{
    this->isSet = false;
}

void ModelViewport::SetViewportSize(const glm::vec4 &vec4)
{
    viewPortSize = vec4;
}

void ModelViewport::SetViewportPosition(const glm::vec4 &vec4)
{
    viewPortPosition = vec4;
}

glm::vec4 & ModelViewport::GetViewportSize()
{
    return viewPortSize;
}

glm::vec4 & ModelViewport::GetViewportPosition()
{
    return viewPortPosition;
}