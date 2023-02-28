//
// Created by erik9 on 12/21/2022.
//

#include "LineModel.h"
#include "Renderer.h"
#include "RenderingApi.h"
#include "Commands.h"

void LineModel::SetStartPont(const glm::vec4 &pos)
{
    startPoint = pos;
}

void LineModel::SetEndPoint(const glm::vec4 &pos)
{
    endPoint = pos;
}

const glm::vec4 & LineModel::GetStartPoint()
{
    return startPoint;
}

const glm::vec4 & LineModel::GetEndPoint()
{
    return endPoint;
}

void LineModel::SetColor(const glm::vec4 &color)
{
    this->color = color;
}

const glm::vec4 & LineModel::GetColor()
{
    return color;
}

void LineModel::Draw()
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

    if(message->GetMessageId() != Commands::Property)
        return;

    if(message->GetSubMessageId() == SubCommands::SetWidth)
    {
        auto width = message->GetData<float>();
        SetWidth(width);
    }
    else if(message->GetSubMessageId() == SubCommands::SetStartPoint)
    {
        auto point = message->GetData<glm::vec4>();
        SetStartPont(point);
    }
    else if(message->GetSubMessageId() == SubCommands::SetEndPoint)
    {
        auto point = message->GetData<glm::vec4>();
        SetEndPoint(point);
    }
    else if(message->GetSubMessageId() == SubCommands::SetColor)
    {
        auto color = message->GetData<glm::vec4>();
        SetColor(color);
    }
}

float LineModel::GetZIndex()
{
    return startPoint.z;
}
