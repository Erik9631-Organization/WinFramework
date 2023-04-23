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
    if(!visible)
        return;
    auto renderer = renderingProvider->AcquireRenderingApi();
    renderer->SetColor(color);
    renderer->DrawLine(startPoint, endPoint);
}

void LineModel::SetRenderer(Renderer *renderer)
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

void LineModel::SetModelId(long long int id)
{
    this->id = id;
}

const size_t & LineModel::GetModelId()
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
    else if(message->GetSubMessageId() == SubCommands::SetVisible)
    {
        auto visible = message->GetData<bool>();
        SetVisible(visible);
    }
}

float LineModel::GetZIndex()
{
    return startPoint.z;
}

void LineModel::SetVisible(bool visible)
{
    this->visible = visible;
}

bool LineModel::IsVisible()
{
    return visible;
}

void LineModel::SetViewportSize(const glm::vec4 &vec4)
{
    viewPort.SetViewportSize(vec4);
    viewPort.NotifyOnViewportSizeChanged({GetViewportPosition(), vec4, this});
}

void LineModel::SetViewportPosition(const glm::vec4 &vec4)
{
    viewPort.SetViewportPosition(vec4);
    viewPort.NotifyOnViewportPositionChanged({GetViewportPosition(), vec4, this});

}

glm::vec4 &LineModel::GetViewportSize()
{
    return viewPort.GetViewportSize();
}

glm::vec4 &LineModel::GetViewportPosition()
{
    return viewPort.GetViewportPosition();
}

void LineModel::ResetViewport()
{
    viewPort.ResetViewport();
}

void LineModel::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPort.AddViewport2Subscriber(subscriber);
}

void LineModel::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPort.RemoveViewport2Subscriber(subscriber);
}

void LineModel::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportSizeChanged(event);
}

void LineModel::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportPositionChanged(event);
}

bool LineModel::IsViewportSet() const
{
    return viewPort.IsViewportSet();
}

void LineModel::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportReset(event);
}
