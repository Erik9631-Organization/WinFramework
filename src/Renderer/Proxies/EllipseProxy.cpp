//
// Created by erik9 on 12/11/2022.
//

#include "EllipseProxy.h"
#include "EventMoveInfo.h"
#include "EventResizeInfo.h"
#include "RenderMessage.h"
#include "EllipseModel.h"
#include <iostream>


const glm::vec3 & EllipseProxy::GetPosition() const
{
    auto tempData = messageSender.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec3&>();
    if(model == nullptr)
        return defaultVector;
    return model->GetPosition();
}

const glm::vec3 & EllipseProxy::GetAbsolutePosition() const
{
    return GetPosition();
}

void EllipseProxy::SetPosition(const glm::vec3 &position, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(position, this);
    renderMessage->SetSubMessageId(SubCommands::SetPosition);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void EllipseProxy::SetTranslate(const glm::vec3 &offset, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(offset, this);
    renderMessage->SetSubMessageId(SubCommands::SetTranslate);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

const glm::vec3 & EllipseProxy::GetTranslate() const
{
    auto tempData = messageSender.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec3&>();
    if(model == nullptr)
        return defaultVector;
    return model->GetTranslate();
}

void EllipseProxy::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.push_back(&subscriber);
}

void EllipseProxy::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
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

void EllipseProxy::NotifyOnMoveSubscribers(const EventMoveInfo &e)
{
    for (auto it = moveSubscribers.begin(); it != moveSubscribers.end(); it++)
        (*it)->OnMove(e);
}

const size_t & EllipseProxy::GetAssociatedModelId()
{
    return renderingModel->GetModelId();
}

void EllipseProxy::OnRenderMessageProcessed(const SubCommands &processedCommand)
{
    messageSender.OnRenderMessageProcessed(processedCommand);
}

void EllipseProxy::OnModelCreated(RenderingModel *model, RenderingConsumer *consumer)
{
    this->model = dynamic_cast<EllipseModel*>(model);
    if (this->model == nullptr)
    {
        std::cout << "EllipseProxy::OnModelCreated: model is not a EllipseModel" << std::endl;
        return;
    }

    messageSender.OnModelCreated(model, consumer);
}

const glm::vec4 &EllipseProxy::GetSize()
{
    auto tempData = messageSender.Get(SubCommands::SetSize);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec4&>();
    if(model == nullptr)
        return defaultVector;

    return model->GetSize();
}

float EllipseProxy::GetWidth()
{
    return GetSize().x;
}

float EllipseProxy::GetHeight()
{
    return GetSize().y;
}

void EllipseProxy::SetSize(const glm::vec4 &size, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(size, this);
    renderMessage->SetSubMessageId(SubCommands::SetSize);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void EllipseProxy::SetSize(glm::vec4 size)
{
    SetSize(size, true);
}

void EllipseProxy::SetSize(float width, float height, bool emit)
{
    SetSize({width, height, 0, 0}, emit);
}

void EllipseProxy::SetSize(float width, float height)
{
    SetSize({width, height, 0, 0}, true);
}

void EllipseProxy::SetWidth(float width, bool emit)
{
    SetSize(width, model->GetHeight(), emit);
}

void EllipseProxy::SetWidth(float width)
{
    SetSize(width, model->GetHeight(), true);
}

void EllipseProxy::SetHeight(float height, bool emit)
{
    SetSize(model->GetWidth(), height, emit);
}

void EllipseProxy::SetHeight(float height)
{
    SetSize(model->GetWidth(), height, true);
}

void EllipseProxy::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    for (auto* subscriber : resizeSubscribers)
        subscriber->OnResize(event);
}

void EllipseProxy::AddOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizeSubscribers.push_back(&subscriber);
}

void EllipseProxy::RemoveOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    for (auto it = resizeSubscribers.begin(); it != resizeSubscribers.end(); it++)
    {
        if (*it == &subscriber)
        {
            resizeSubscribers.erase(it);
            return;
        }
    }
}

void EllipseProxy::SetColor(const glm::ivec4 &color)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(color, this);
    renderMessage->SetSubMessageId(SubCommands::SetColor);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

const glm::ivec4 & EllipseProxy::GetColor()
{
    auto tempData = messageSender.Get(SubCommands::SetColor);
    if(tempData != nullptr)
        return tempData->GetData<const glm::ivec4&>();
    if(model == nullptr)
        return defaultColorVec;
    return model->GetColor();
}

void EllipseProxy::SetFill(bool fill)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(fill, this);
    renderMessage->SetSubMessageId(SubCommands::SetFill);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

bool EllipseProxy::GetFill()
{
    auto tempData = messageSender.Get(SubCommands::SetColor);
    if(tempData != nullptr)
        return tempData->GetData<const bool>();
    if(model == nullptr)
        return false;
    return model->GetFill();
}

void EllipseProxy::SetVisible(bool visible)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(visible, this);
    renderMessage->SetSubMessageId(SubCommands::SetVisible);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

bool EllipseProxy::IsVisible()
{
    auto tempData = messageSender.Get(SubCommands::SetVisible);
    if(tempData != nullptr)
        return tempData->GetData<const bool>();
    return model->IsVisible();
}

SubCommands EllipseProxy::GetModelRequestCommand()
{
    return SubCommands::RequestEllipse;
}

void EllipseProxy::SetViewportSize(const glm::vec4 &viewPort)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(viewPort, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortSize);
    messageSender.SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportSizeChanged({GetViewportPosition(), viewPort, this});
}

void EllipseProxy::SetViewportPosition(const glm::vec3 &input)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(input, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortPosition);
    messageSender.SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportPositionChanged({input, GetViewportSize(), this});
}

void EllipseProxy::ResetViewport()
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(nullptr, this);
    renderMessage->SetSubMessageId(SubCommands::ResetViewPort);
    messageSender.SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportReset({GetViewportPosition(), GetViewportSize(), this});
}

const glm::vec4 & EllipseProxy::GetViewportSize()
{
    auto tempData = messageSender.Get(SubCommands::SetViewPortPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4& >();
    if(model == nullptr)
        return defaultVector;
    return model->GetViewportSize();
}

const glm::vec3 & EllipseProxy::GetViewportPosition()
{
    auto tempData = messageSender.Get(SubCommands::SetViewPortSize);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4&>();
    if(model == nullptr)
        return defaultVector;
    return model->GetViewportSize();
}

void EllipseProxy::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPortSubscribers.push_back(&subscriber);
}

void EllipseProxy::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPortSubscribers.erase(std::remove(viewPortSubscribers.begin(), viewPortSubscribers.end(), &subscriber), viewPortSubscribers.end());
}

void EllipseProxy::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    for(auto* subscriber : viewPortSubscribers)
        subscriber->OnViewportSizeChanged(event);
}

void EllipseProxy::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    for(auto* subscriber : viewPortSubscribers)
        subscriber->OnViewportPositionChanged(event);
}

bool EllipseProxy::IsViewportSet() const
{
    return model->IsViewportSet();
}

void EllipseProxy::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    for(auto* subscriber : viewPortSubscribers)
        subscriber->OnViewportReset(event);
}
