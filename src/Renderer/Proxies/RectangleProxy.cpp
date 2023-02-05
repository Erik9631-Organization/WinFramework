//
// Created by erik9 on 12/11/2022.
//

#include "RectangleProxy.h"
#include "RenderingConsumer.h"
#include "Commands.h"
#include "RectangleModel.h"
#include "EventMoveInfo.h"
#include <iostream>

glm::vec4 RectangleProxy::GetPosition()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>();

    return model->GetPosition();
}

float RectangleProxy::GetX()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().x;

    return model->GetX();
}

float RectangleProxy::GetY()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().y;

    return model->GetY();
}

float RectangleProxy::GetZ()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().z;

    return model->GetZ();
}

float RectangleProxy::GetW()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().w;

    return model->GetW();
}

void RectangleProxy::SetPosition(glm::vec4 position, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(0, position, this);
    renderMessage->SetSubMessageId(SubCommands::SetPosition);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::SetPosition(glm::vec4 position)
{
    SetPosition(position, true);
}

void RectangleProxy::SetPosition(float x, float y, float z, float w, bool emit)
{
    SetPosition({x, y, z, w}, emit);
}

void RectangleProxy::SetPosition(float x, float y, float z, float w)
{
    SetPosition(x, y, z, w, true);
}

void RectangleProxy::SetX(float x, bool emit)
{
    SetPosition(x, model->GetY(), model->GetZ(), model->GetW(), emit);
}

void RectangleProxy::SetX(float x)
{
    SetPosition(x, model->GetY(), model->GetZ(), model->GetW(), true);
}

void RectangleProxy::SetY(float y, bool emit)
{
    SetPosition(model->GetX(), y, model->GetZ(), model->GetW(), emit);
}

void RectangleProxy::SetY(float y)
{
    SetPosition(model->GetX(), y, model->GetZ(), model->GetW(), true);
}

void RectangleProxy::SetZ(float z, bool emit)
{
    SetPosition(model->GetX(), model->GetY(), z, model->GetW(), emit);
}

void RectangleProxy::SetZ(float z)
{
    SetPosition(model->GetX(), model->GetY(), z, model->GetW(), true);
}

void RectangleProxy::SetW(float w, bool emit)
{
    SetPosition(model->GetX(), model->GetY(), model->GetZ(), w, emit);
}

void RectangleProxy::SetW(float w)
{
    SetPosition(model->GetX(), model->GetY(), model->GetZ(), w, true);
}

void RectangleProxy::SetTranslate(glm::vec4 offset, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(0, offset, this);
    renderMessage->SetSubMessageId(SubCommands::SetTranslate);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::SetTranslate(glm::vec4 offset)
{
    SetTranslate(offset, true);
}

void RectangleProxy::SetTranslateX(float x, bool emit)
{
    SetTranslate({x, model->GetTranslateY(), 0, 0}, emit);
}

void RectangleProxy::SetTranslateX(float x)
{
    SetTranslateX(x, true);
}

void RectangleProxy::SetTranslateY(float y, bool emit)
{
    SetTranslate({model->GetTranslateX(), y, 0, 0}, emit);
}

void RectangleProxy::SetTranslateY(float y)
{
    SetTranslateY(y, true);
}

glm::vec4 RectangleProxy::GetTranslate()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>();

    return model->GetTranslate();
}

float RectangleProxy::GetTranslateX()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().x;

    return model->GetTranslateX();
}

float RectangleProxy::GetTranslateY()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().y;

    return model->GetTranslateY();
}

glm::vec4 RectangleProxy::GetSize()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetSize);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>();

    return model->GetSize();
}

float RectangleProxy::GetWidth()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetSize);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().x;
    return model->GetWidth();
}

float RectangleProxy::GetHeight()
{
    auto tempData = copyOnWriteMap.Get(SubCommands::SetSize);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().y;
    return model->GetHeight();
}

void RectangleProxy::SetSize(glm::vec4 size, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(0, size, this);
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
    return model->GetX();
}

float RectangleProxy::GetAbsoluteY()
{
    return model->GetY();
}

glm::vec4 RectangleProxy::GetAbsolutePosition()
{
    return model->GetAbsolutePosition();
}

size_t & RectangleProxy::GetAssociatedModelId()
{
    return model->GetModelId();
}

void RectangleProxy::OnModelCreated(RenderingModel *model)
{
    if(preInitMessages == nullptr)
        return;

    //Send the messages before the model is assigned, to guarantee ordering
    std::unique_ptr<RenderMessage> message;
    while(preInitMessages->try_dequeue(message))
    {
        message->SetReceiverId(model->GetModelId());
        renderingConsumer->ReceiveCommand(std::move(message));
    }
    std::lock_guard<std::mutex> lock(modelSetMutex);
    this->model = dynamic_cast<RectangleModel*>(model);

    //Throw away the queue as it is no longer needed after we have the model
    delete preInitMessages;
    preInitMessages = nullptr;
}

void RectangleProxy::SendRenderingMessage(std::unique_ptr<RenderMessage> message)
{
    copyOnWriteMap.Add(message->GetSubMessageId(), message.get());
    std::lock_guard<std::mutex> lock(modelSetMutex);
    if(model == nullptr)
    {
        if(preInitMessages == nullptr)
        {
            std::cout << "preInitMessages is null!" << std::endl;
            return;
        }
        preInitMessages->enqueue(std::move(message));
        return;
    }

    message->SetReceiverId(model->GetModelId());
    renderingConsumer->ReceiveCommand(std::move(message));
}

void RectangleProxy::SetColor(const glm::vec4 &color)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(0, color, this);
    renderMessage->SetSubMessageId(SubCommands::SetColor);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::SetFill(bool fill)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(0, fill, this);
    renderMessage->SetSubMessageId(SubCommands::SetFill);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::OnRenderMessageProcessed(const SubCommands &processedCommand)
{
    copyOnWriteMap.Remove(processedCommand);
}

RectangleProxy::RectangleProxy() : copyOnWriteMap(totalCommands)
{
    preInitMessages = new moodycamel::ConcurrentQueue<std::unique_ptr<RenderMessage>>();
}

const ModelViewport& RectangleProxy::GetViewport() const
{
    return model->GetViewPort();
}

void RectangleProxy::SetViewPortSize(const glm::vec2 &size)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(0, size, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortSize);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::SetViewPortPosition(const glm::vec2& position)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(0, position, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortPosition);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::ResetViewPort()
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(0, nullptr, this);
    renderMessage->SetSubMessageId(SubCommands::ResetViewPort);
    SendRenderingMessage(std::move(renderMessage));
}

void RectangleProxy::BindViewPortToMovable(Movable &movable)
{
    movableViewportBinding = &movable;
    movable.AddOnMoveSubscriber(*this);
    SetPosition(movable.GetAbsolutePosition());
}

void RectangleProxy::BindViewPortToResizable(Resizable &resizable)
{
    resizableViewportBinding = &resizable;
    resizable.AddOnResizeSubscriber(*this);
    SetViewPortSize(resizable.GetSize());
}

void RectangleProxy::UnbindViewPortMovable()
{
    movableViewportBinding->RemoveOnMoveSubscriber(*this);
    movableViewportBinding = nullptr;
}

void RectangleProxy::UnbindViewportResizable()
{
    resizableViewportBinding->RemoveOnResizeSubscriber(*this);
    resizableViewportBinding = nullptr;
}

void RectangleProxy::OnMove(EventMoveInfo e)
{
    if (e.GetSrc() != movableViewportBinding)
        return;

    SetViewPortPosition(e.GetPosition());
}

void RectangleProxy::OnResize(EventResizeInfo e)
{
    if (e.GetSrc() != resizableViewportBinding)
        return;

    SetViewPortSize(e.GetSize());
}

RectangleProxy::~RectangleProxy()
{
    if (movableViewportBinding)
        UnbindViewPortMovable();

    if (resizableViewportBinding)
        UnbindViewportResizable();
}

