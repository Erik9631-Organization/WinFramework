//
// Created by erik9 on 4/18/2023.
//

#include "EllipseModel.h"
#include "EventMoveInfo.h"
#include "Commands.h"
#include "Renderer.h"

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
            auto position = message->GetData<glm::vec4>();
            SetPosition(position);
            break;
        }
        case SubCommands::SetX:
        {
            auto x = message->GetData<float>();
            SetX(x);
            break;
        }
        case SubCommands::SetY:
        {
            auto y = message->GetData<float>();
            SetY(y);
            break;
        }
        case SubCommands::SetSize:
        {
            auto size = message->GetData<glm::vec4>();
            SetSize(size);
            break;
        }
        case SubCommands::SetTranslate:
        {
            auto translate = message->GetData<glm::vec4>();
            SetTranslate(translate);
            break;
        }
        case SubCommands::SetTranslateX:
        {
            auto translateX = message->GetData<float>();
            SetTranslateX(translateX);
            break;
        }
        case SubCommands::SetTranslateY:
        {
            auto translateY = message->GetData<float>();
            SetTranslateY(translateY);
            break;
        }
        case SubCommands::SetWidth:
        {
            auto width = message->GetData<float>();
            SetWidth(width);
            break;
        }
        case SubCommands::SetHeight:
        {
            auto height = message->GetData<float>();
            SetHeight(height);
            break;
        }
        case SubCommands::SetViewPortSize:
        {
            viewPort.SetViewPortSize(message->GetData<glm::vec2>());
            break;
        }
        case SubCommands::SetViewPortPosition:
        {
            viewPort.SetViewPortPosition(message->GetData<glm::vec2>());
            break;
        }
        case SubCommands::ResetViewPort:
        {
            ResetViewport();
            break;
        }
        default:
            break;
    }
}

void EllipseModel::ResetViewport()
{
    viewPort.ResetViewPort();
}


float EllipseModel::GetZIndex()
{
    return movableBehavior.GetZ();
}

void EllipseModel::Draw()
{
    auto renderingApi = this->renderer->AcquireRenderingApi();
    if(renderingApi == nullptr)
        return;
    renderingApi->SetColor(color);
    if(viewPort.IsSet())
        renderingApi->SetClippingRectangle(viewPort.GetViewPortPosition(), viewPort.GetViewPortSize());

    if(fill)
        renderingApi->DrawFillEllipse(movableBehavior.GetX(), movableBehavior.GetY(), resizableBehavior.GetWidth(), resizableBehavior.GetHeight());
    else
        renderingApi->DrawEllipse(movableBehavior.GetX(), movableBehavior.GetY(), resizableBehavior.GetWidth(), resizableBehavior.GetHeight());

}

void EllipseModel::SetRenderer(Renderer *renderer)
{
    this->renderer = renderer;
}

void EllipseModel::SetModelId(long long int id)
{
    this->id = id;
}

long long int & EllipseModel::GetModelId()
{
    return id;
}

glm::vec4 EllipseModel::GetPosition()
{
    return movableBehavior.GetPosition();
}

float EllipseModel::GetX()
{
    return movableBehavior.GetX();
}

float EllipseModel::GetY()
{
    return movableBehavior.GetY();
}

float EllipseModel::GetZ()
{
    return movableBehavior.GetZ();
}

float EllipseModel::GetW()
{
    return movableBehavior.GetW();
}

float EllipseModel::GetAbsoluteX()
{
    return movableBehavior.GetAbsoluteX();
}

float EllipseModel::GetAbsoluteY()
{
    return movableBehavior.GetAbsoluteY();
}

const glm::vec4 &EllipseModel::GetAbsolutePosition()
{
    return movableBehavior.GetAbsolutePosition();
}

void EllipseModel::SetPosition(glm::vec4 position, bool emit)
{
    movableBehavior.SetPosition(position);
}

void EllipseModel::SetPosition(glm::vec4 position)
{
    movableBehavior.SetPosition(position);
}

void EllipseModel::SetPosition(float x, float y, float z, float w, bool emit)
{
    movableBehavior.SetPosition(x, y, z, w, emit);
}

void EllipseModel::SetPosition(float x, float y, float z, float w)
{
    movableBehavior.SetPosition(x, y, z, w);
}

void EllipseModel::SetX(float x, bool emit)
{
    movableBehavior.SetX(x, emit);
}

void EllipseModel::SetX(float x)
{
    movableBehavior.SetX(x);
}

void EllipseModel::SetY(float y, bool emit)
{
    movableBehavior.SetY(y, emit);
}

void EllipseModel::SetY(float y)
{
    movableBehavior.SetY(y);
}

void EllipseModel::SetZ(float z, bool emit)
{
    movableBehavior.SetZ(z, emit);
}

void EllipseModel::SetZ(float z)
{
    movableBehavior.SetZ(z);
}

void EllipseModel::SetW(float w, bool emit)
{
    movableBehavior.SetW(w, emit);
}

void EllipseModel::SetW(float w)
{
    movableBehavior.SetW(w);
}

void EllipseModel::SetTranslate(glm::vec4 offset, bool emit)
{
    movableBehavior.SetTranslate(offset, emit);
}

void EllipseModel::SetTranslate(glm::vec4 offset)
{
    movableBehavior.SetTranslate(offset);
}

void EllipseModel::SetTranslateX(float x, bool emit)
{
    movableBehavior.SetTranslateX(x, emit);
}

void EllipseModel::SetTranslateX(float x)
{
    movableBehavior.SetTranslateX(x);
}

void EllipseModel::SetTranslateY(float y, bool emit)
{
    movableBehavior.SetTranslateY(y, emit);
}

void EllipseModel::SetTranslateY(float y)
{
    movableBehavior.SetTranslateY(y);
}

glm::vec4 EllipseModel::GetTranslate()
{
    return movableBehavior.GetTranslate();
}

float EllipseModel::GetTranslateX()
{
    return movableBehavior.GetTranslateX();
}

float EllipseModel::GetTranslateY()
{
    return movableBehavior.GetTranslateY();
}

const glm::vec4 &EllipseModel::GetSize()
{
    return resizableBehavior.GetSize();
}

float EllipseModel::GetWidth()
{
    return resizableBehavior.GetWidth();
}

float EllipseModel::GetHeight()
{
    return resizableBehavior.GetHeight();
}

void EllipseModel::SetSize(glm::vec4 size, bool emit)
{
    resizableBehavior.SetSize(size, emit);
}

void EllipseModel::SetSize(glm::vec4 size)
{
    resizableBehavior.SetSize(size);
}

void EllipseModel::SetSize(float width, float height, bool emit)
{
    resizableBehavior.SetSize(width, height, emit);
}

void EllipseModel::SetSize(float width, float height)
{
    resizableBehavior.SetSize(width, height);
}

void EllipseModel::SetWidth(float width, bool emit)
{
    resizableBehavior.SetWidth(width, emit);
}

void EllipseModel::SetWidth(float width)
{
    resizableBehavior.SetWidth(width);
}

void EllipseModel::SetHeight(float height, bool emit)
{
    resizableBehavior.SetHeight(height, emit);
}

void EllipseModel::SetHeight(float height)
{
    resizableBehavior.SetHeight(height);
}

void EllipseModel::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    movableBehavior.AddOnMoveSubscriber(subscriber);
}

void EllipseModel::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{
    movableBehavior.RemoveOnMoveSubscriber(subscriber);
}

void EllipseModel::NotifyOnMoveSubscribers(EventMoveInfo e)
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
