//
// Created by erik9 on 12/21/2022.
//

#include "LineModel.h"
#include "Renderer.h"
#include "RenderingApi.h"
#include "Commands.h"

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
    auto renderer = renderingProvider->AcquireRenderingApi();
    renderer->SetColor(color);
    renderer->DrawLine(startPoint, endPoint);
}

void LineModel::SetRenderingProvider(Renderer *renderer)
{
    this->renderingProvider = renderer;
}

void LineModel::SetWidth(float width)
{
    this->width = width;
}

const float &LineModel::GetWidth()
{
    return width;
}

void LineModel::SetAssociatedModelId(unsigned long long int id)
{
    this->id = id;
}

size_t & LineModel::GetModelId()
{
    return id;
}

void LineModel::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    if(message->GetReceiverId() != id)
        return;

    if(message->GetId() != Commands::Property)
        return;

    if(message->GetSubId() == PropertyCommandIds::SetWidth)
    {
        auto width = message->GetData<float>();
        SetWidth(width);
    }
    else if(message->GetSubId() == PropertyCommandIds::SetStartPoint)
    {
        auto point = message->GetData<glm::vec2>();
        SetStartPont(point);
    }
    else if(message->GetSubId() == PropertyCommandIds::SetEndPoint)
    {
        auto point = message->GetData<glm::vec2>();
        SetEndPoint(point);
    }
    else if(message->GetSubId() == PropertyCommandIds::SetColor)
    {
        auto color = message->GetData<Vector4>();
        SetColor(color);
    }
}

float LineModel::GetZIndex()
{
    return 100000;
}
