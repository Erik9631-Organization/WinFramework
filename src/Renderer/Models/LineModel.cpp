//
// Created by erik9 on 12/21/2022.
//

#include "LineModel.h"

void LineModel::SetStartPont(const glm::vec2 &pos)
{
    startPoint = pos;
}

void LineModel::SetEndPoint(const glm::vec2 &pos)
{
    endPoint = pos;
}

const glm::vec2 &LineModel::GetStartPoint()
{
    return startPoint;
}

const glm::vec2 &LineModel::GetEndPoint()
{
    return endPoint;
}

void LineModel::SetColor(const Vector4 &color)
{
    this->color = color;
}

const Vector4 &LineModel::GetColor()
{
    return color;
}

void LineModel::Redraw()
{
    renderer->DrawLine(startPoint, endPoint);
}

void LineModel::SetRenderer(Renderer *renderer)
{
    this->renderer = renderer;
}

void LineModel::SetWidth(float width)
{
    this->width = width;
}

const float &LineModel::GetWidth()
{
    return width;
}
