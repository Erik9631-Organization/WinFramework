//
// Created by erik9 on 12/11/2022.
//

#include "TextProxy.h"
#include "EventMoveInfo.h"
#include "TextModel.h"

glm::vec4 TextProxy::GetPosition()
{
    auto tempData = messageSender.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>();
    return model->GetPosition();
}

float TextProxy::GetX()
{
    auto tempData = messageSender.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().x;

    return model->GetX();
}

float TextProxy::GetY()
{
    auto tempData = messageSender.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().y;

    return model->GetY();
}

float TextProxy::GetZ()
{
    auto tempData = messageSender.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().z;

    return model->GetZ();
}

float TextProxy::GetW()
{
    auto tempData = messageSender.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().w;

    return model->GetW();
}

float TextProxy::GetAbsoluteX()
{
    return model->GetX();
}

float TextProxy::GetAbsoluteY()
{
    return model->GetY();
}

glm::vec4 TextProxy::GetAbsolutePosition()
{
    return model->GetAbsolutePosition();
}

void TextProxy::SetPosition(glm::vec4 position, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(position, this);
    renderMessage->SetSubMessageId(SubCommands::SetPosition);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void TextProxy::SetPosition(glm::vec4 position)
{
    SetPosition(position, true);
}

void TextProxy::SetPosition(float x, float y, float z, float w, bool emit)
{
    SetPosition({x, y, z, w}, emit);
}

void TextProxy::SetPosition(float x, float y, float z, float w)
{
    SetPosition(x, model->GetY(), model->GetZ(), model->GetW(), true);
}

void TextProxy::SetX(float x, bool emit)
{
    SetPosition(x, model->GetY(), model->GetZ(), model->GetW(), emit);
}

void TextProxy::SetX(float x)
{
    SetPosition(x, model->GetY(), model->GetZ(), model->GetW(), true);
}

void TextProxy::SetY(float y, bool emit)
{
    SetPosition(model->GetX(), y, model->GetZ(), model->GetW(), emit);
}

void TextProxy::SetY(float y)
{
    SetPosition(model->GetX(), y, model->GetZ(), model->GetW(), true);
}

void TextProxy::SetZ(float z, bool emit)
{
    SetPosition(model->GetX(), model->GetY(), z, model->GetW(), emit);
}

void TextProxy::SetZ(float z)
{
    SetPosition(model->GetX(), model->GetY(), z, model->GetW(), true);
}

void TextProxy::SetW(float w, bool emit)
{
    SetPosition(model->GetX(), model->GetY(), model->GetZ(), w, emit);
}

void TextProxy::SetW(float w)
{
    SetPosition(model->GetX(), model->GetY(), model->GetZ(), w, true);
}

void TextProxy::SetTranslate(glm::vec4 offset, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(offset, this);
    renderMessage->SetSubMessageId(SubCommands::SetTranslate);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void TextProxy::SetTranslate(glm::vec4 offset)
{
    SetTranslate(offset, true);
}

void TextProxy::SetTranslateX(float x, bool emit)
{
    SetTranslate({x, model->GetTranslateY(), 0, 0}, emit);
}

void TextProxy::SetTranslateX(float x)
{
    SetTranslateX(x, true);
}

void TextProxy::SetTranslateY(float y, bool emit)
{
    SetTranslate({model->GetTranslateX(), y, 0, 0}, emit);
}

void TextProxy::SetTranslateY(float y)
{
    SetTranslateY(y, true);
}

glm::vec4 TextProxy::GetTranslate()
{
    auto tempData = messageSender.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>();

    return model->GetTranslate();
}

float TextProxy::GetTranslateX()
{
    auto tempData = messageSender.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().x;

    return model->GetTranslateX();
}

float TextProxy::GetTranslateY()
{
    auto tempData = messageSender.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4>().y;

    return model->GetTranslateY();
}

void TextProxy::OnRenderMessageProcessed(const SubCommands &processedCommand)
{
    messageSender.OnRenderMessageProcessed(processedCommand);
}

size_t &TextProxy::GetAssociatedModelId()
{
    return id;
}

void TextProxy::OnModelCreated(RenderingModel *model, RenderingConsumer *consumer)
{
    messageSender.OnModelCreated(model, consumer);
    this->model = dynamic_cast<TextModel*>(model);
}


void TextProxy::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.push_back(&subscriber);
}

void TextProxy::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
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

void TextProxy::NotifyOnMoveSubscribers(EventMoveInfo e)
{
    for (auto it = moveSubscribers.begin(); it != moveSubscribers.end(); it++)
        (*it)->OnMove(e);
}

void TextProxy::OnMove(EventMoveInfo e)
{
    SetPosition(e.GetPosition(), true);
}
