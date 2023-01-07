//
// Created by erik9 on 12/12/2022.
//

#include "RectangleModel.h"
#include "EventMoveInfo.h"
#include "Renderer.h"
#include "Commands.h"
#include "RenderingProvider.h"
#include "Vector3.h"

glm::vec2 RectangleModel::GetPosition()
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

float RectangleModel::GetAbsoluteX()
{
    return movableBehavior.GetAbsoluteX();
}

float RectangleModel::GetAbsoluteY()
{
    return movableBehavior.GetAbsoluteY();
}

glm::vec2 RectangleModel::GetAbsolutePosition()
{
    return movableBehavior.GetAbsolutePosition();
}

void RectangleModel::SetPosition(glm::vec2 position, bool emit)
{
    movableBehavior.SetPosition(position, emit);
}

void RectangleModel::SetPosition(glm::vec2 position)
{
    movableBehavior.SetPosition(position);
}

void RectangleModel::SetPosition(float x, float y, bool emit)
{
    movableBehavior.SetPosition(x, y, emit);
}

void RectangleModel::SetPosition(float x, float y)
{
    movableBehavior.SetPosition(x, y);
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

void RectangleModel::SetTranslate(glm::vec2 offset, bool emit)
{
    movableBehavior.SetTranslate(offset, emit);
}

void RectangleModel::SetTranslate(glm::vec2 offset)
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

glm::vec2 RectangleModel::GetTranslate()
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

glm::vec2 RectangleModel::GetSize()
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

void RectangleModel::SetSize(glm::vec2 size, bool emit)
{
    resizableBehavior.SetSize(size, emit);
}

void RectangleModel::SetSize(glm::vec2 size)
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

void RectangleModel::NotifyOnMoveSubscribers(EventMoveInfo e)
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

void RectangleModel::Redraw()
{
    auto renderer = this->rendereringProvider->AcquireRenderer();
    if(renderer == nullptr)
        return;
    renderer->SetColor(color);
    if(fill)
        renderer->DrawFillRectangle(movableBehavior.GetAbsoluteX(), movableBehavior.GetAbsoluteY(), resizableBehavior.GetWidth(), resizableBehavior.GetHeight());
    else
        renderer->DrawRectangle(movableBehavior.GetAbsoluteX(), movableBehavior.GetAbsoluteY(), resizableBehavior.GetWidth(), resizableBehavior.GetHeight());
}

void RectangleModel::SetColor(const Vector4 &color)
{
    this->color = color;
}

const Vector4 &RectangleModel::GetColor() const
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

void RectangleModel::SetRenderingProvider(RenderingProvider *renderer)
{
    this->rendereringProvider = renderer;
}

void RectangleModel::SetAssociatedModelId(unsigned long long int id)
{
    this->id = id;
}

long long int & RectangleModel::GetModelId()
{
    return id;
}

void RectangleModel::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    if(message->GetReceiverId() != id)
        return;

    if(message->GetId() != Commands::Property)
        return;

    switch (message->GetSubId())
    {
        case PropertyCommandIds::SetWidth:
            SetWidth(message->GetData<float>());
            break;
        case PropertyCommandIds::SetHeight:
            SetHeight(message->GetData<float>());
            break;
        case PropertyCommandIds::SetSize:
            SetSize(message->GetData<glm::vec2>());
            break;
        case PropertyCommandIds::SetX:
            SetX(message->GetData<float>());
            break;
        case PropertyCommandIds::SetY:
            SetY(message->GetData<float>());
            break;
        case PropertyCommandIds::SetPosition:
            SetPosition(message->GetData<glm::vec2>());
            break;
        case PropertyCommandIds::SetTranslate:
            SetTranslate(message->GetData<glm::vec2>());
            break;
        case PropertyCommandIds::SetColor:
            SetColor(message->GetData<Vector4>());
            break;
        case PropertyCommandIds::SetFill:
            SetFill(message->GetData<bool>());
            break;
        default:
            break;
    }
}
