//
// Created by erik9 on 12/12/2022.
//

#include "RectangleModel.h"
#include "EventMoveInfo.h"
#include "RenderingApi.h"
#include "Commands.h"
#include <iostream>

const glm::vec4 & RectangleModel::GetPosition()
{
    return movableBehavior.GetPosition();
}

float RectangleModel::GetX()
{
    return movableBehavior.GetX();
}

float RectangleModel::GetY()
{
    return movableBehavior.GetY();
}

float RectangleModel::GetZ()
{
    return movableBehavior.GetZ();
}

float RectangleModel::GetW()
{
    return movableBehavior.GetW();
}

float RectangleModel::GetAbsoluteX()
{
    return movableBehavior.GetAbsoluteX();
}

float RectangleModel::GetAbsoluteY()
{
    return movableBehavior.GetAbsoluteY();
}

const glm::vec4 & RectangleModel::GetAbsolutePosition()
{
    return movableBehavior.GetAbsolutePosition();
}

void RectangleModel::SetPosition(const glm::vec4 &position, bool emit)
{
    movableBehavior.SetPosition(position, emit);
}

void RectangleModel::SetPosition(glm::vec4 position)
{
    movableBehavior.SetPosition(position);
}

void RectangleModel::SetPosition(float x, float y, float z, float w, bool emit)
{
    movableBehavior.SetPosition(x, y, z, w, emit);
}

void RectangleModel::SetPosition(float x, float y, float z, float w)
{
    movableBehavior.SetPosition(x, y, 0, 0);
}

void RectangleModel::SetX(float x, bool emit)
{
    movableBehavior.SetX(x, emit);
}

void RectangleModel::SetX(float x)
{
    movableBehavior.SetX(x);
}

void RectangleModel::SetY(float y, bool emit)
{
    movableBehavior.SetY(y, emit);
}

void RectangleModel::SetY(float y)
{
    movableBehavior.SetY(y);
}

void RectangleModel::SetZ(float z, bool emit)
{
    movableBehavior.SetZ(z, emit);
}

void RectangleModel::SetZ(float z)
{
    movableBehavior.SetZ(z);
}

void RectangleModel::SetW(float w, bool emit)
{
    movableBehavior.SetW(w, emit);
}

void RectangleModel::SetW(float w)
{
    movableBehavior.SetW(w);
}

void RectangleModel::SetTranslate(const glm::vec4 &offset, bool emit)
{
    movableBehavior.SetTranslate(offset, emit);
}

void RectangleModel::SetTranslate(glm::vec4 offset)
{
    movableBehavior.SetTranslate(offset);
}

void RectangleModel::SetTranslateX(float x, bool emit)
{
    movableBehavior.SetTranslateX(x, emit);
}

void RectangleModel::SetTranslateX(float x)
{
    movableBehavior.SetTranslateX(x);
}

void RectangleModel::SetTranslateY(float y, bool emit)
{
    movableBehavior.SetTranslateY(y, emit);
}

void RectangleModel::SetTranslateY(float y)
{
    movableBehavior.SetTranslateY(y);
}

const glm::vec4 & RectangleModel::GetTranslate()
{
    return movableBehavior.GetTranslate();
}

float RectangleModel::GetTranslateX()
{
    return movableBehavior.GetTranslateX();
}

float RectangleModel::GetTranslateY()
{
    return movableBehavior.GetTranslateY();
}

const glm::vec4 & RectangleModel::GetSize()
{
    return resizableBehavior.GetSize();
}

float RectangleModel::GetWidth()
{
    return resizableBehavior.GetWidth();
}

float RectangleModel::GetHeight()
{
    return resizableBehavior.GetHeight();
}

void RectangleModel::SetSize(const glm::vec4 &size, bool emit)
{
    resizableBehavior.SetSize(size, emit);
}

void RectangleModel::SetSize(glm::vec4 size)
{
    resizableBehavior.SetSize(size);
}

void RectangleModel::SetSize(float width, float height, bool emit)
{
    resizableBehavior.SetSize(width, height, emit);
}

void RectangleModel::SetSize(float width, float height)
{
    resizableBehavior.SetSize(width, height);
}

void RectangleModel::SetWidth(float width, bool emit)
{
    resizableBehavior.SetWidth(width, emit);
}

void RectangleModel::SetWidth(float width)
{
    resizableBehavior.SetWidth(width);
}

void RectangleModel::SetHeight(float height, bool emit)
{
    resizableBehavior.SetHeight(height, emit);
}

void RectangleModel::SetHeight(float height)
{
    resizableBehavior.SetHeight(height);
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

    auto renderingApi = this->renderer->AcquireRenderingApi();
    if(renderingApi == nullptr)
        return;
    renderingApi->SetColor(color);
    //TODO Viewport position should serve only as an offset to the current position.
    if(viewPort.IsViewportSet())
        renderingApi->SetClippingRectangle(viewPort.GetViewportPosition(), viewPort.GetViewportSize());

    if(fill)
        renderingApi->DrawFillRectangle(movableBehavior.GetX(), movableBehavior.GetY(), resizableBehavior.GetWidth(), resizableBehavior.GetHeight());
    else
    {
        renderingApi->SetThickness(thickness);
        renderingApi->DrawRectangle(movableBehavior.GetX(), movableBehavior.GetY(), resizableBehavior.GetWidth(), resizableBehavior.GetHeight());
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
        case SubCommands::SetWidth:
            SetWidth(message->GetData<float>());
            break;
        case SubCommands::SetHeight:
            SetHeight(message->GetData<float>());
            break;
        case SubCommands::SetSize:
            SetSize(message->GetData<glm::vec4>());
            break;
        case SubCommands::SetX:
            SetX(message->GetData<float>());
            break;
        case SubCommands::SetY:
            SetY(message->GetData<float>());
            break;
        case SubCommands::SetPosition:
            SetPosition(message->GetData<glm::vec4>());
            break;
        case SubCommands::SetTranslate:
            SetTranslate(message->GetData<glm::vec4>());
            break;
        case SubCommands::SetColor:
            SetColor(message->GetData<glm::ivec4>());
            break;
        case SubCommands::SetFill:
            SetFill(message->GetData<bool>());
            break;
        case SubCommands::SetViewPortSize:
        {
            SetViewportSize(message->GetData<glm::vec4>());
            break;
        }
        case SubCommands::SetViewPortPosition:
        {
            SetViewportPosition(message->GetData<glm::vec4>());
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
    return movableBehavior.GetZ();
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

void RectangleModel::SetViewportSize(const glm::vec4 &vec4)
{
    viewPort.SetViewportSize(vec4);
    viewPort.NotifyOnViewportSizeChanged({vec4, GetViewportPosition(), this});
}

void RectangleModel::SetViewportPosition(const glm::vec4 &vec4)
{
    viewPort.SetViewportPosition(vec4);
    NotifyOnViewportPositionChanged({vec4, GetViewportPosition(), this});
}

const glm::vec4 & RectangleModel::GetViewportSize()
{
    return viewPort.GetViewportSize();
}

const glm::vec4 & RectangleModel::GetViewportPosition()
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
