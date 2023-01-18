//
// Created by erik9 on 1/17/2023.
//

#include "ModelViewport.h"

void ModelViewport::SetViewPortSize(const glm::vec2 &size)
{
    viewPortPosition = size;
}

void ModelViewport::SetViewPortPosition(const glm::vec2 &position)
{
    viewPortPosition = position;
}

void ModelViewport::SetViewPortX(float x)
{
    SetViewPortSize({x, viewPortPosition.y});
}

void ModelViewport::SetViewPortY(float y)
{
    SetViewPortSize({viewPortPosition.x, y});
}

void ModelViewport::SetViewPortWidth(float width)
{
    SetViewPortSize({width, viewPortSize.y});
}

void ModelViewport::SetViewPortHeight(float height)
{
    SetViewPortSize({viewPortSize.x, height});
}

const glm::vec2 &ModelViewport::GetViewPortSize() const
{
    return viewPortSize;
}

const glm::vec2 &ModelViewport::GetViewPortPosition() const
{
    return viewPortPosition;
}

float ModelViewport::GetViewPortX() const
{
    return viewPortPosition.x;
}

float ModelViewport::GetViewPortY() const
{
    return viewPortPosition.y;
}

float ModelViewport::GetViewPortWidth() const
{
    return viewPortSize.x;
}

float ModelViewport::GetViewPortHeight() const
{
    return viewPortSize.y;
}