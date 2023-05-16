//
// Created by erik9 on 4/18/2023.
//

#include "EllipseModel.h"
#include "EventMoveInfo.h"
#include "Commands.h"
#include "Renderer.h"
#include "Utils.hpp"

void EllipseModel::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    switch (message->GetSubMessageId())
    {
        case SubCommands::SetFill:
        {
            fill = message->GetData<bool>();
            break;
        }
        case SubCommands::SetColor:
        {
            color = message->GetData<glm::ivec4>();
            break;
        }
        case SubCommands::SetPosition:
        {
            auto position = message->GetData<glm::vec3>();
            SetPosition(position);
            break;
        }
        case SubCommands::SetSize:
        {
            auto size = message->GetData<glm::vec3>();
            SetSize(size);
            break;
        }
        case SubCommands::SetTranslate:
        {
            auto translate = message->GetData<glm::vec3>();
            SetTranslate(translate);
            break;
        }
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
        case SubCommands::SetVisible:
        {
            visible = message->GetData<bool>();
            break;
        }
        default:
            break;
    }
}

void EllipseModel::ResetViewport()
{
    viewPort.ResetViewport();
}


float EllipseModel::GetZIndex()
{
    return movableBehavior.GetPosition().z;
}

void EllipseModel::Draw()
{
    if(!visible)
        return;
    auto calculatedPosition = movableBehavior.GetPosition();
    if(renderFromCenter)
        calculatedPosition = TranslateFromCornerToCenter(calculatedPosition, resizableBehavior.GetSize());

    auto renderingApi = this->renderer->AcquireShapeRenderer();
    if(renderingApi == nullptr)
        return;
    renderingApi->SetColor(color);
    if(viewPort.IsViewportSet())
        renderingApi->SetClippingRectangle(calculatedPosition + viewPort.GetViewportPosition(),
                                           viewPort.GetViewportSize());

    if(fill)
        renderingApi->DrawFillEllipse(calculatedPosition, resizableBehavior.GetSize());
    else
        renderingApi->DrawEllipse(calculatedPosition, resizableBehavior.GetSize());

}

void EllipseModel::SetRenderer(Renderer *renderer)
{
    this->renderer = renderer;
}

void EllipseModel::SetModelId(size_t id)
{
    this->id = id;
}

const size_t & EllipseModel::GetModelId()
{
    return id;
}

const glm::vec3 & EllipseModel::GetPosition() const
{
    return movableBehavior.GetPosition();
}


const glm::vec3 & EllipseModel::GetAbsolutePosition() const
{
    return movableBehavior.GetAbsolutePosition();
}

void EllipseModel::SetPosition(const glm::vec3 &position, bool emit)
{
    movableBehavior.SetPosition(position, emit);
}

void EllipseModel::SetTranslate(const glm::vec3 &offset, bool emit)
{
    movableBehavior.SetTranslate(offset, emit);
}

const glm::vec3 & EllipseModel::GetTranslate() const
{
    return movableBehavior.GetTranslate();
}

const glm::vec3 & EllipseModel::GetSize() const
{
    return resizableBehavior.GetSize();
}

void EllipseModel::SetSize(const glm::vec3 &size, bool emit)
{
    resizableBehavior.SetSize(size, emit);
}


void EllipseModel::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    movableBehavior.AddOnMoveSubscriber(subscriber);
}

void EllipseModel::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{
    movableBehavior.RemoveOnMoveSubscriber(subscriber);
}

void EllipseModel::NotifyOnMoveSubscribers(const EventMoveInfo &e)
{
    movableBehavior.NotifyOnMoveSubscribers(e);
}

void EllipseModel::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    resizableBehavior.NotifyOnResizeSubscribers(event);
}

void EllipseModel::AddOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizableBehavior.AddOnResizeSubscriber(subscriber);
}

void EllipseModel::RemoveOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizableBehavior.RemoveOnResizeSubscriber(subscriber);
}

void EllipseModel::SetColor(const glm::ivec4 &color)
{
    this->color = color;
}

const glm::ivec4 & EllipseModel::GetColor()
{
    return color;
}

EllipseModel::EllipseModel() : movableBehavior(*this)
{

}

void EllipseModel::SetFill(bool fill)
{
    this->fill = fill;
}

bool EllipseModel::GetFill() const
{
    return fill;
}

void EllipseModel::SetVisible(bool visible)
{
    this->visible = visible;
}

bool EllipseModel::IsVisible()
{
    return visible;
}

void EllipseModel::SetRenderFromCenter(bool renderFromCenter)
{
    this->renderFromCenter = renderFromCenter;
}

bool EllipseModel::GetRenderFromCenter() const
{
    return renderFromCenter;
}

void EllipseModel::SetViewportSize(const glm::vec3 &input)
{
    viewPort.SetViewportSize(input);
    viewPort.NotifyOnViewportSizeChanged({GetViewportPosition(), input, this});
}

void EllipseModel::SetViewportPosition(const glm::vec3 &input)
{
    viewPort.SetViewportPosition(input);
    viewPort.NotifyOnViewportSizeChanged({input, GetViewportSize(), this});
}

const glm::vec3 & EllipseModel::GetViewportSize()
{
    return viewPort.GetViewportSize();
}

const glm::vec3 & EllipseModel::GetViewportPosition()
{
    return viewPort.GetViewportPosition();
}

void EllipseModel::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPort.AddViewport2Subscriber(subscriber);
}

void EllipseModel::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPort.RemoveViewport2Subscriber(subscriber);
}

void EllipseModel::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportSizeChanged(event);
}

void EllipseModel::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportPositionChanged(event);
}

bool EllipseModel::IsViewportSet() const
{
    return viewPort.IsViewportSet();
}

void EllipseModel::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportReset(event);
}