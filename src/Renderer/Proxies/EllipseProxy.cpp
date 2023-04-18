//
// Created by erik9 on 12/11/2022.
//

#include "EllipseProxy.h"
#include "EventMoveInfo.h"
#include "EventResizeInfo.h"
#include "RenderMessage.h"
#include "EllipseModel.h"
#include <iostream>


glm::vec4 EllipseProxy::GetPosition()
{
    auto tempData = messageSender.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec4&>();
    return model->GetPosition();
}

float EllipseProxy::GetX()
{
    return GetPosition().x;
}

float EllipseProxy::GetY()
{
    return GetPosition().y;
}

float EllipseProxy::GetAbsoluteX()
{
    return GetPosition().x;
}

float EllipseProxy::GetAbsoluteY()
{
    return GetPosition().y;
}

const glm::vec4 & EllipseProxy::GetAbsolutePosition()
{
    return GetPosition();
}

void EllipseProxy::SetPosition(glm::vec4 position, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(position, this);
    renderMessage->SetSubMessageId(SubCommands::SetPosition);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void EllipseProxy::SetPosition(glm::vec4 position)
{
    SetPosition(position, true);
}

void EllipseProxy::SetPosition(float x, float y, float z, float w, bool emit)
{
    SetPosition({x, y, z, w}, emit);
}

void EllipseProxy::SetPosition(float x, float y, float z, float w)
{
    SetPosition({x, y, z, w}, true);
}

void EllipseProxy::SetX(float x, bool emit)
{
    SetPosition(x, model->GetY(), model->GetZ(), model->GetW(), emit);
}

void EllipseProxy::SetX(float x)
{
    SetPosition(x, model->GetY(), model->GetZ(), model->GetW(), true);
}

void EllipseProxy::SetY(float y, bool emit)
{
    SetPosition(model->GetX(), y, model->GetZ(), model->GetW(), emit);
}

void EllipseProxy::SetY(float y)
{
    SetPosition(model->GetX(), y, model->GetZ(), model->GetW(), true);
}

void EllipseProxy::SetTranslate(glm::vec4 offset, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(offset, this);
    renderMessage->SetSubMessageId(SubCommands::SetTranslate);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void EllipseProxy::SetTranslate(glm::vec4 offset)
{
    SetTranslate(offset, true);
}

void EllipseProxy::SetTranslateX(float x, bool emit)
{
    SetTranslate({x, model->GetTranslateY(), 0, 0}, emit);
}

void EllipseProxy::SetTranslateX(float x)
{
    SetTranslate({x, model->GetTranslateY(), 0, 0}, true);
}

void EllipseProxy::SetTranslateY(float y, bool emit)
{
    SetTranslate({model->GetTranslateX(), y, 0, 0}, emit);
}

void EllipseProxy::SetTranslateY(float y)
{
    SetTranslate({model->GetTranslateX(), y, 0, 0}, true);
}

glm::vec4 EllipseProxy::GetTranslate()
{
    auto tempData = messageSender.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec4&>();
    return model->GetTranslate();
}

float EllipseProxy::GetTranslateX()
{
    auto tempData = messageSender.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().x;

    return model->GetTranslateX();
}

float EllipseProxy::GetTranslateY()
{
    auto tempData = messageSender.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().y;

    return model->GetTranslateY();
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

void EllipseProxy::NotifyOnMoveSubscribers(EventMoveInfo e)
{
    for (auto it = moveSubscribers.begin(); it != moveSubscribers.end(); it++)
        (*it)->OnMove(e);
}

const size_t & EllipseProxy::GetAssociatedModelId()
{
    return renderingModel->GetModelId();
}

float EllipseProxy::GetZ()
{
    return GetPosition().z;
}

float EllipseProxy::GetW()
{
    return GetPosition().w;
}

void EllipseProxy::SetZ(float z, bool emit)
{
    SetPosition(model->GetX(), model->GetY(), z, model->GetW(), emit);
}

void EllipseProxy::SetZ(float z)
{
    SetPosition(model->GetX(), model->GetY(), z, model->GetW(), true);
}

void EllipseProxy::SetW(float w, bool emit)
{
    SetPosition(model->GetX(), model->GetY(), model->GetZ(), w, emit);
}

void EllipseProxy::SetW(float w)
{
    SetPosition(model->GetX(), model->GetY(), model->GetZ(), w, true);
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
        std::cout << "RectangleProxy::OnModelCreated: model is not a RectangleModel" << std::endl;
        return;
    }

    messageSender.OnModelCreated(model, consumer);
}

const glm::vec4 &EllipseProxy::GetSize()
{
    auto tempData = messageSender.Get(SubCommands::SetSize);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec4&>();

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
