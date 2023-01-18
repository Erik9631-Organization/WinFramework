//
// Created by erik9 on 12/11/2022.
//

#include "RectangleProxy.h"
#include "RenderingConsumer.h"
#include "Commands.h"
#include "RectangleModel.h"
#include "EventMoveInfo.h"

glm::vec4 RectangleProxy::GetPosition()
{
    auto it = copyOnWriteMap.find(SubCommands::SetPosition);
    if(it == copyOnWriteMap.end())
        return model->GetPosition();

    return it->second->GetData<glm::vec4>();
}

float RectangleProxy::GetX()
{

    auto it = copyOnWriteMap.find(SubCommands::SetPosition);
    if(it == copyOnWriteMap.end())
        return model->GetX();

    return it->second->GetData<glm::vec4>().x;
}

float RectangleProxy::GetY()
{
    auto it = copyOnWriteMap.find(SubCommands::SetPosition);
    if(it == copyOnWriteMap.end())
        return model->GetY();

    return it->second->GetData<glm::vec4>().y;
}

float RectangleProxy::GetZ()
{
    auto it = copyOnWriteMap.find(SubCommands::SetPosition);
    if(it == copyOnWriteMap.end())
        return model->GetZ();

    return it->second->GetData<glm::vec4>().z;
}

float RectangleProxy::GetW()
{
    auto it = copyOnWriteMap.find(SubCommands::SetPosition);
    if(it == copyOnWriteMap.end())
        return model->GetW();

    return it->second->GetData<glm::vec4>().w;
}

void RectangleProxy::SetPosition(glm::vec4 position, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), position);
    renderMessage->SetSubMessageId(SubCommands::SetPosition);
    copyOnWriteMap.emplace(renderMessage->GetSubMessageId(), renderMessage.get());
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
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
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), offset);
    renderMessage->SetSubMessageId(SubCommands::SetTranslate);
    copyOnWriteMap.emplace(renderMessage->GetSubMessageId(), renderMessage.get());
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
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
    auto it = copyOnWriteMap.find(SubCommands::SetTranslate);
    if(it == copyOnWriteMap.end())
        return model->GetTranslate();

    return it->second->GetData<glm::vec4>();
}

float RectangleProxy::GetTranslateX()
{
    auto it = copyOnWriteMap.find(SubCommands::SetTranslate);
    if(it == copyOnWriteMap.end())
        return model->GetTranslateX();

    return it->second->GetData<glm::vec4>().x;
}

float RectangleProxy::GetTranslateY()
{
    auto it = copyOnWriteMap.find(SubCommands::SetTranslate);
    if(it == copyOnWriteMap.end())
        return model->GetTranslateY();

    return it->second->GetData<glm::vec4>().y;
}

glm::vec4 RectangleProxy::GetSize()
{
    auto it = copyOnWriteMap.find(SubCommands::SetSize);
    if(it == copyOnWriteMap.end())
        return model->GetSize();

    return it->second->GetData<glm::vec4>();
}

float RectangleProxy::GetWidth()
{
    auto it = copyOnWriteMap.find(SubCommands::SetSize);
    if(it == copyOnWriteMap.end())
        return model->GetWidth();

    return it->second->GetData<glm::vec4>().x;
}

float RectangleProxy::GetHeight()
{
    auto it = copyOnWriteMap.find(SubCommands::SetSize);
    if(it == copyOnWriteMap.end())
        return model->GetHeight();

    return it->second->GetData<glm::vec4>().y;
}

void RectangleProxy::SetSize(glm::vec4 size, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), size);
    renderMessage->SetSubMessageId(SubCommands::SetSize);
    copyOnWriteMap.emplace(renderMessage->GetSubMessageId(), renderMessage.get());
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
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
    return 0;
}

float RectangleProxy::GetAbsoluteY()
{
    return 0;
}

glm::vec4 RectangleProxy::GetAbsolutePosition()
{
    return glm::vec4();
}

size_t & RectangleProxy::GetAssociatedModelId()
{
    return model->GetModelId();
}

void RectangleProxy::SetAssociatedModel(RenderingModel *model)
{
    this->model = dynamic_cast<RectangleModel*>(model);
}

void RectangleProxy::SetColor(const glm::vec4 &color)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), color);
    renderMessage->SetSubMessageId(SubCommands::SetColor);
    copyOnWriteMap.emplace(renderMessage->GetSubMessageId(), renderMessage.get());
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

void RectangleProxy::SetFill(bool fill)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), fill);
    renderMessage->SetSubMessageId(SubCommands::SetFill);
    copyOnWriteMap.emplace(renderMessage->GetSubMessageId(), renderMessage.get());
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

void RectangleProxy::OnRenderMessageProcessed(const SubCommands &processedCommand)
{
    copyOnWriteMap.erase(processedCommand);
}

RectangleProxy::RectangleProxy()
{
    copyOnWriteMap.reserve(totalCommands);
}

const ModelViewport& RectangleProxy::GetViewport() const
{
    return model->GetViewPort();
}

void RectangleProxy::SetViewPortSize(const glm::vec2 &size)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), size);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortSize);
    copyOnWriteMap.emplace(renderMessage->GetSubMessageId(), renderMessage.get());
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}

void RectangleProxy::SetViewPortPosition(const glm::vec2& position)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(model->GetModelId(), position);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortPosition);
    copyOnWriteMap.emplace(renderMessage->GetSubMessageId(), renderMessage.get());
    renderingConsumer->ReceiveCommand(std::move(renderMessage));
}
