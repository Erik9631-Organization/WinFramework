//
// Created by erik9 on 12/11/2022.
//

#include "RectangleProxy.h"
#include "RenderingConsumer.h"
#include "Commands.h"
#include "RectangleModel.h"
#include "EventMoveInfo.h"

glm::vec2 RectangleProxy::GetPosition()
{
    return model->GetPosition();
}

float RectangleProxy::GetX()
{
    return model->GetX();
}

float RectangleProxy::GetY()
{
    return model->GetY();
}

void RectangleProxy::SetPosition(glm::vec2 position, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), position);
    renderMessage->SetSubMessageId(SubCommands::SetPosition);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

void RectangleProxy::SetPosition(glm::vec2 position)
{
    SetPosition(position, true);
}

void RectangleProxy::SetPosition(float x, float y, bool emit)
{
    SetPosition({x, y}, emit);
}

void RectangleProxy::SetPosition(float x, float y)
{
    SetPosition(x, y, true);
}

void RectangleProxy::SetX(float x, bool emit)
{
    SetPosition(x, model->GetY(), emit);
}

void RectangleProxy::SetX(float x)
{
    SetPosition(x, false);
}

void RectangleProxy::SetY(float y, bool emit)
{
    SetPosition(model->GetX(),y , emit);
}

void RectangleProxy::SetY(float y)
{
    SetPosition(model->GetX(), y, false);
}

void RectangleProxy::SetTranslate(glm::vec2 offset, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), offset);
    renderMessage->SetSubMessageId(SubCommands::SetTranslate);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

void RectangleProxy::SetTranslate(glm::vec2 offset)
{
    SetTranslate(offset, true);
}

void RectangleProxy::SetTranslateX(float x, bool emit)
{
    SetTranslate({x, model->GetTranslateY()}, emit);
}

void RectangleProxy::SetTranslateX(float x)
{
    SetTranslateX(x, true);
}

void RectangleProxy::SetTranslateY(float y, bool emit)
{
    SetTranslate({model->GetTranslateX(), y}, emit);
}

void RectangleProxy::SetTranslateY(float y)
{
    SetTranslateY(y, true);
}

glm::vec2 RectangleProxy::GetTranslate()
{
    return model->GetTranslate();
}

float RectangleProxy::GetTranslateX()
{
    return model->GetTranslateX();
}

float RectangleProxy::GetTranslateY()
{
    return model->GetTranslateY();
}

glm::vec2 RectangleProxy::GetSize()
{
    return model->GetSize();
}

float RectangleProxy::GetWidth()
{
    return model->GetWidth();
}

float RectangleProxy::GetHeight()
{
    return model->GetHeight();
}

void RectangleProxy::SetSize(glm::vec2 size, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), size);
    renderMessage->SetSubMessageId(SubCommands::SetSize);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

void RectangleProxy::SetSize(glm::vec2 size)
{
    SetSize(size, true);
}

void RectangleProxy::SetSize(float width, float height, bool emit)
{
    SetSize({width, height}, emit);
}

void RectangleProxy::SetSize(float width, float height)
{
    SetSize(width, height, true);
}

void RectangleProxy::SetWidth(float width, bool emit)
{
    SetSize(width, model->GetHeight(), emit);
}

void RectangleProxy::SetWidth(float width)
{
    SetWidth(width, true);
}

void RectangleProxy::SetHeight(float height, bool emit)
{
    SetSize(model->GetWidth(), height, emit);
}

void RectangleProxy::SetHeight(float height)
{
    SetHeight(height, true);
}

void RectangleProxy::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.push_back(&subscriber);
}

void RectangleProxy::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{
    for (auto it = moveSubscribers.begin(); it != moveSubscribers.end(); it++)
    {
        if (*it == &subscriber)
        {
            moveSubscribers.erase(it);
            break;
        }
    }

}


void RectangleProxy::NotifyOnMoveSubscribers(EventMoveInfo e)
{
    for (auto it = moveSubscribers.begin(); it != moveSubscribers.end(); it++)
    {
        (*it)->OnMove(e);
    }
}

void RectangleProxy::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    for (auto* subscriber : resizeSubscribers)
    {
        subscriber->OnResize(event);
    }
}

void RectangleProxy::AddOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizeSubscribers.push_back(&subscriber);
}

void RectangleProxy::RemoveOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    for (auto it = resizeSubscribers.begin(); it != resizeSubscribers.end(); it++)
    {
        if (*it == &subscriber)
        {
            resizeSubscribers.erase(it);
            break;
        }
    }
}

void RectangleProxy::SetRenderingConsumer(RenderingConsumer *consumer)
{
    this->renderingConsumer = consumer;
}

float RectangleProxy::GetAbsoluteX()
{
    return 0;
}

float RectangleProxy::GetAbsoluteY()
{
    return 0;
}

glm::vec2 RectangleProxy::GetAbsolutePosition()
{
    return glm::vec2(0);
}

size_t & RectangleProxy::GetAssociatedModelId()
{
    return model->GetModelId();
}

void RectangleProxy::SetAssociatedModel(RenderingModel *model)
{
    this->model = dynamic_cast<RectangleModel*>(model);
}

void RectangleProxy::SetColor(const Vector4 &color)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), color);
    renderMessage->SetSubMessageId(SubCommands::SetColor);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

void RectangleProxy::SetFill(bool fill)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), fill);
    renderMessage->SetSubMessageId(SubCommands::SetFill);
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}
