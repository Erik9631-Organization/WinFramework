//
// Created by erik9 on 12/12/2022.
//

#include "RectangleModel.h"
#include "EventMoveInfo.h"
#include "ShapeRenderer.h"
#include "Commands.h"
#include <iostream>

const glm::vec3 & RectangleModel::GetPosition() const
{
    return movableBehavior.GetPosition();
}

const glm::vec3 & RectangleModel::GetAbsolutePosition() const
{
    return movableBehavior.GetAbsolutePosition();
}

void RectangleModel::SetPosition(const glm::vec3 &position, bool emit)
{
    movableBehavior.SetPosition(position, emit);
}


void RectangleModel::SetTranslate(const glm::vec3 &offset, bool emit)
{
    movableBehavior.SetTranslate(offset, emit);
}


const glm::vec3 & RectangleModel::GetTranslate() const
{
    return movableBehavior.GetTranslate();
}

const glm::vec3 & RectangleModel::GetSize() const
{
    return resizableBehavior.GetSize();
}

void RectangleModel::SetSize(const glm::vec3 &size, bool emit)
{
    resizableBehavior.SetSize(size, emit);
}

void RectangleModel::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    movableBehavior.AddOnMoveSubscriber(subscriber);
}

void RectangleModel::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{
    movableBehavior.RemoveOnMoveSubscriber(subscriber);
}

void RectangleModel::NotifyOnMoveSubscribers(const EventMoveInfo &e)
{
    movableBehavior.NotifyOnMoveSubscribers(e);
}

void RectangleModel::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    resizableBehavior.NotifyOnResizeSubscribers(event);
}

void RectangleModel::AddOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizableBehavior.AddOnResizeSubscriber(subscriber);
}

void RectangleModel::RemoveOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizableBehavior.RemoveOnResizeSubscriber(subscriber);
}

void RectangleModel::Draw()
{
    if(!visible)
        return;

    auto renderingApi = this->renderer->AcquireShapeRenderer();
    if(renderingApi == nullptr)
        return;
    renderingApi->SetColor(color);
    //TODO Viewport position should serve only as an offset to the current position.
    if(viewPort.IsViewportSet())
        renderingApi->SetClippingRectangle(viewPort.GetViewportPosition(), viewPort.GetViewportSize());

    if(fill)
        renderingApi->DrawFillRectangle(movableBehavior.GetPosition(), resizableBehavior.GetSize());
    else
    {
        renderingApi->SetThickness(thickness);
        renderingApi->DrawRectangle(movableBehavior.GetPosition(), resizableBehavior.GetSize());
    }

}

void RectangleModel::SetColor(const glm::vec4 &color)
{
    this->color = color;
}

const glm::ivec4 & RectangleModel::GetColor() const
{
    return color;
}

void RectangleModel::SetFill(bool fill)
{
    this->fill = fill;
}

const bool &RectangleModel::GetFill() const
{
    return fill;
}

void RectangleModel::SetRenderer(Renderer *renderer)
{
    this->renderer = renderer;
}

void RectangleModel::SetModelId(size_t id)
{
    this->id = id;
}

const size_t & RectangleModel::GetModelId()
{
    return id;
}

void RectangleModel::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    if(message->GetReceiverId() != id)
        return;

    if(message->GetMessageId() != Commands::Property)
        return;

    switch (message->GetSubMessageId())
    {
        case SubCommands::SetSize:
            SetSize(message->GetData<glm::vec3>());
            break;
        case SubCommands::SetPosition:
            SetPosition(message->GetData<glm::vec3>());
            break;
        case SubCommands::SetTranslate:
            SetTranslate(message->GetData<glm::vec3>());
            break;
        case SubCommands::SetColor:
            SetColor(message->GetData<glm::ivec4>());
            break;
        case SubCommands::SetFill:
            SetFill(message->GetData<bool>());
            break;
        case SubCommands::SetViewPortSize:
        {
            SetViewportSize(message->GetData<glm::vec3>());
            break;
        }
        case SubCommands::SetViewPortPosition:
        {
            SetViewportPosition(message->GetData<glm::vec3>());
            break;
        }
        case SubCommands::ResetViewPort:
        {
            ResetViewport();
            break;
        }
        case SubCommands::SetThickness:
        {
            SetThickness(message->GetData<float>());
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

float RectangleModel::GetZIndex()
{
    return movableBehavior.GetPosition().z;
}


bool RectangleModel::IsViewPortSet()
{
    return viewPort.IsViewportSet();
}

void RectangleModel::ResetViewport()
{
    viewPort.ResetViewport();
}

const ModelViewport &RectangleModel::GetViewPort() const
{
    return viewPort;
}

RectangleModel::RectangleModel() : movableBehavior(*this)
{

}

float RectangleModel::GetThickness() const
{
    return thickness;
}

void RectangleModel::SetThickness(float thickness)
{
    this->thickness = thickness;
}

void RectangleModel::SetVisible(bool visible)
{
    this->visible = visible;
}

bool RectangleModel::IsVisible()
{
    return visible;
}

void RectangleModel::SetViewportSize(const glm::vec3 &input)
{
    viewPort.SetViewportSize(input);
    viewPort.NotifyOnViewportSizeChanged({GetViewportPosition(), input, this});
}

void RectangleModel::SetViewportPosition(const glm::vec3 &input)
{
    viewPort.SetViewportPosition(input);
    NotifyOnViewportPositionChanged({input, GetViewportSize(), this});
}

const glm::vec3 & RectangleModel::GetViewportSize()
{
    return viewPort.GetViewportSize();
}

const glm::vec3 & RectangleModel::GetViewportPosition()
{
    return viewPort.GetViewportPosition();
}

void RectangleModel::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPort.AddViewport2Subscriber(subscriber);
}

void RectangleModel::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPort.RemoveViewport2Subscriber(subscriber);
}

void RectangleModel::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportSizeChanged(event);
}

void RectangleModel::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportPositionChanged(event);
}

bool RectangleModel::IsViewportSet() const
{
    return viewPort.IsViewportSet();
}

void RectangleModel::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportReset(event);
}
