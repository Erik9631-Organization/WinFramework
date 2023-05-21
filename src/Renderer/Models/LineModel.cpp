//
// Created by erik9 on 12/21/2022.
//

#include "LineModel.h"
#include "Renderer.h"
#include "ShapeRenderer.h"
#include "Commands.h"
#include "EventMoveInfo.h"
#include "MoveSubscriber.h"

void LineModel::SetStartPont(const glm::vec3 &pos)
{
    startPoint = pos;
}

void LineModel::SetEndPoint(const glm::vec3 &pos)
{
    endPoint = pos;
}

const glm::vec3 & LineModel::GetStartPoint()
{
    return startPoint;
}

const glm::vec3 & LineModel::GetEndPoint()
{
    return endPoint;
}

void LineModel::SetColor(const glm::ivec4 &color)
{
    this->color = color;
}

const glm::ivec4 & LineModel::GetColor()
{
    return color;
}

void LineModel::Draw()
{
    if(!visible)
        return;
    auto& renderer = renderingProvider->AcquireShapeRenderer();
    renderer.SetColor(color);
    renderer.SetThickness(size);
    renderer.DrawLine(startPoint + position, endPoint + position);
}

void LineModel::SetRenderer(Renderer *renderer)
{
    this->renderingProvider = renderer;
}

void LineModel::SetSize(float size)
{
    this->size = size;
}

float LineModel::GetSize() const
{
    return size;
}

void LineModel::SetModelId(size_t id)
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

    switch(message->GetSubMessageId())
    {
        case SubCommands::SetSize:
        {
            SetSize(message->GetData<float>());
            break;
        }
        case SubCommands::SetStartPoint:
        {
            SetStartPont(message->GetData<glm::vec3>());
            break;
        }
        case SubCommands::SetEndPoint:
        {
            SetEndPoint(message->GetData<glm::vec3>());
            break;
        }
        case SubCommands::SetColor:
        {
            SetColor(message->GetData<glm::ivec4>());
            break;
        }
        case SubCommands::SetVisible:
        {
            SetVisible(message->GetData<bool>());
            break;
        }
        default:
            break;
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

void LineModel::SetViewportSize(const glm::vec3 &input)
{
    viewPort.SetViewportSize(input);
    viewPort.NotifyOnViewportSizeChanged({GetViewportPosition(), input, this});
}

void LineModel::SetViewportPosition(const glm::vec3 &input)
{
    viewPort.SetViewportPosition(input);
    viewPort.NotifyOnViewportPositionChanged({input, GetViewportSize(), this});

}

const glm::vec3 & LineModel::GetViewportSize()
{
    return viewPort.GetViewportSize();
}

const glm::vec3 & LineModel::GetViewportPosition()
{
    return viewPort.GetViewportPosition();
}

void LineModel::ResetViewport()
{
    viewPort.ResetViewport();
}

void LineModel::AddViewportSubscriber(ViewportSubscriber &subscriber)
{
    viewPort.AddViewportSubscriber(subscriber);
}

void LineModel::RemoveViewportSubscriber(ViewportSubscriber &subscriber)
{
    viewPort.RemoveViewportSubscriber(subscriber);
}

void LineModel::NotifyOnViewportSizeChanged(const ViewportEventInfo &event)
{
    viewPort.NotifyOnViewportSizeChanged(event);
}

void LineModel::NotifyOnViewportPositionChanged(const ViewportEventInfo &event)
{
    viewPort.NotifyOnViewportPositionChanged(event);
}

bool LineModel::IsViewportSet() const
{
    return viewPort.IsViewportSet();
}

void LineModel::NotifyOnViewportReset(const ViewportEventInfo &event)
{
    viewPort.NotifyOnViewportReset(event);
}

void LineModel::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.push_back(&subscriber);
}

void LineModel::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.erase(std::remove(moveSubscribers.begin(), moveSubscribers.end(), &subscriber), moveSubscribers.end());
}

void LineModel::NotifyOnMoveSubscribers(const EventMoveInfo &e)
{
    for(auto &subscriber : moveSubscribers)
        subscriber->OnMove(e);
}

const glm::vec3 &LineModel::GetPosition() const
{
    return position;
}

const glm::vec3 &LineModel::GetAbsolutePosition() const
{
    return position;
}

void LineModel::SetPosition(const glm::vec3 &position, bool emit)
{
    this->position = position;
    if(emit)
        NotifyOnMoveSubscribers({position, position, this});
}

void LineModel::SetTranslate(const glm::vec3 &offset, bool emit)
{
    translate = offset;
}

const glm::vec3 &LineModel::GetTranslate() const
{
    return translate;
}
