//
// Created by erik9 on 12/11/2022.
//

#include "RectangleProxy.h"
#include "RenderingConsumer.h"
#include "Commands.h"
#include "RectangleModel.h"
#include "EventMoveInfo.h"
#include <iostream>

const glm::vec3 & RectangleProxy::GetPosition() const
{
    auto tempData = messageSender.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec3&>();
    if(model == nullptr)
        return defaultVec4;

    return model->GetPosition();
}


void RectangleProxy::SetPosition(const glm::vec3 &position, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(position, this);
    renderMessage->SetSubMessageId(SubCommands::SetPosition);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::SetTranslate(const glm::vec3 &offset, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(offset, this);
    renderMessage->SetSubMessageId(SubCommands::SetTranslate);
    SendRenderingMessage(std::move(renderMessage));
}

const glm::vec3 & RectangleProxy::GetTranslate() const
{
    auto tempData = messageSender.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec3&>();
    if(model == nullptr)
        return defaultVec4;

    return model->GetTranslate();
}


const glm::vec4 & RectangleProxy::GetSize()
{
    auto tempData = messageSender.Get(SubCommands::SetSize);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec4&>();
    if(model != nullptr)
        return defaultVec4;

    return model->GetSize();
}

float RectangleProxy::GetWidth()
{
    auto tempData = messageSender.Get(SubCommands::SetSize);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().x;
    if(model != nullptr)
        return 0.0f;
    return model->GetWidth();
}

float RectangleProxy::GetHeight()
{
    auto tempData = messageSender.Get(SubCommands::SetSize);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().y;
    if(model != nullptr)
        return 0.0f;
    return model->GetHeight();
}

void RectangleProxy::SetSize(const glm::vec4 &size, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(size, this);
    renderMessage->SetSubMessageId(SubCommands::SetSize);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::SetSize(glm::vec4 size)
{
    SetSize(size, true);
}

void RectangleProxy::SetSize(float width, float height, bool emit)
{
    SetSize({width, height, 0, 0}, emit);
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

void RectangleProxy::NotifyOnMoveSubscribers(const EventMoveInfo &e)
{
    for (auto it = moveSubscribers.begin(); it != moveSubscribers.end(); it++)
        (*it)->OnMove(e);
}

void RectangleProxy::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    for (auto* subscriber : resizeSubscribers)
        subscriber->OnResize(event);
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

const glm::vec3 & RectangleProxy::GetAbsolutePosition() const
{
    return GetPosition();
}

const size_t & RectangleProxy::GetAssociatedModelId()
{
    return model->GetModelId();
}

void RectangleProxy::OnModelCreated(RenderingModel *model, RenderingConsumer *consumer)
{
    this->model = dynamic_cast<RectangleModel*>(model);
    if (this->model == nullptr)
    {
        std::cout << "RectangleProxy::OnModelCreated: model is not a RectangleModel" << std::endl;
        return;
    }

    messageSender.OnModelCreated(model, consumer);

}

void RectangleProxy::SendRenderingMessage(std::unique_ptr<RenderMessage> message)
{
    messageSender.SendRenderingMessage(std::move(message));
}

void RectangleProxy::SetColor(const glm::ivec4 &color)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(color, this);
    renderMessage->SetSubMessageId(SubCommands::SetColor);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::SetFill(bool fill)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(fill, this);
    renderMessage->SetSubMessageId(SubCommands::SetFill);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::OnRenderMessageProcessed(const SubCommands &processedCommand)
{
    messageSender.OnRenderMessageProcessed(processedCommand);
}

void RectangleProxy::OnMove(EventMoveInfo e)
{
    SetPosition(e.GetPosition());
}

void RectangleProxy::OnResize(EventResizeInfo e)
{
    SetSize(e.GetSize());
}

void RectangleProxy::SetThickness(float thickness)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(thickness, this);
    renderMessage->SetSubMessageId(SubCommands::SetThickness);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::SetVisible(bool visible)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(visible, this);
    renderMessage->SetSubMessageId(SubCommands::SetVisible);
    SendRenderingMessage(std::move(renderMessage));
}

bool RectangleProxy::IsVisible()
{
    auto tempData = messageSender.Get(SubCommands::SetVisible);
    if(tempData != nullptr)
        return tempData->GetData<bool>();
    return model->IsVisible();
}

SubCommands RectangleProxy::GetModelRequestCommand()
{
    return SubCommands::RequestRectangle;
}

const glm::ivec4 &RectangleProxy::GetColor()
{
    auto tempData = messageSender.Get(SubCommands::SetColor);
    if(tempData != nullptr)
        return tempData->GetData<const glm::ivec4&>();
    if(model == nullptr)
        return defaultColorVec;
    return model->GetColor();
}

void RectangleProxy::SetViewportSize(const glm::vec4 &vec4)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(vec4, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortSize);
    SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportSizeChanged({GetViewportPosition(), vec4, this});

}

void RectangleProxy::SetViewportPosition(const glm::vec3 &input)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(input, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortPosition);
    SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportPositionChanged({input, GetViewportSize(), this});
}

const glm::vec4 & RectangleProxy::GetViewportSize()
{
    auto tempData = messageSender.Get(SubCommands::SetViewPortSize);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4&>();
    if(model == nullptr)
        return defaultVec4;

    return model->GetViewportSize();
}

const glm::vec3 & RectangleProxy::GetViewportPosition()
{
    auto tempData = messageSender.Get(SubCommands::SetViewPortPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec3&>();
    if(model == nullptr)
        return defaultVec4;
    return model->GetViewportPosition();
}

void RectangleProxy::ResetViewport()
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(nullptr, this);
    renderMessage->SetSubMessageId(SubCommands::ResetViewPort);
    SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportReset({GetViewportPosition(), GetViewportSize(), this});
}

void RectangleProxy::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPortSubscribers.push_back(&subscriber);
}

void RectangleProxy::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPortSubscribers.erase(std::remove(viewPortSubscribers.begin(), viewPortSubscribers.end(), &subscriber), viewPortSubscribers.end());
}

void RectangleProxy::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    for(auto* subscriber : viewPortSubscribers)
        subscriber->OnViewportSizeChanged(event);
}

void RectangleProxy::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    for(auto* subscriber : viewPortSubscribers)
        subscriber->OnViewportPositionChanged(event);
}

bool RectangleProxy::IsViewportSet() const
{
    return model->IsViewportSet();
}

void RectangleProxy::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    for(auto* subscriber : viewPortSubscribers)
        subscriber->OnViewportReset(event);
}
