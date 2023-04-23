//
// Created by erik9 on 1/17/2023.
//

#include "ModelViewport.h"

bool ModelViewport::IsSet() const
{
    return isSet;
}

void ModelViewport::ResetViewPort()
{
    this->isSet = false;
}

void ModelViewport::SetViewPortSize(const glm::vec4 &vec4)
{
    viewPortSize = vec4;
}

void ModelViewport::SetViewPortPosition(const glm::vec4 &vec4)
{
    viewPortPosition = vec4;
}

glm::vec4 & ModelViewport::GetViewPortSize()
{
    return viewPortSize;
}

glm::vec4 & ModelViewport::GetViewPortPosition()
{
    return viewPortPosition;
}