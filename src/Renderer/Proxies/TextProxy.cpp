//
// Created by erik9 on 12/11/2022.
//

#include "TextProxy.h"
#include "EventMoveInfo.h"
#include "TextModel.h"
#include <iostream>

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

const glm::vec4 & TextProxy::GetAbsolutePosition()
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

const size_t & TextProxy::GetAssociatedModelId()
{
    return id;
}

void TextProxy::OnModelCreated(RenderingModel *model, RenderingConsumer *consumer)
{
    this->model = dynamic_cast<TextModel*>(model);
    if (this->model == nullptr)
    {
        std::cout << "Error: TextProxy::OnModelCreated: model is not a TextModel" << std::endl;
    }
    messageSender.OnModelCreated(model, consumer);

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

void TextProxy::SetFontSize(float fontSize)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(fontSize, this);
    renderMessage->SetSubMessageId(SubCommands::SetFontSize);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void TextProxy::SetFontAlignment(FontAlignment alignment)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(alignment, this);
    renderMessage->SetSubMessageId(SubCommands::SetFontAlignment);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void TextProxy::SetFontLineAlignment(FontAlignment alignment)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(alignment, this);
    renderMessage->SetSubMessageId(SubCommands::SetFontLineAlignment);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void TextProxy::SetColor(const glm::ivec4 &color)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(color, this);
    renderMessage->SetSubMessageId(SubCommands::SetColor);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void TextProxy::SetFontFamily(const std::wstring &fontFamily)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(fontFamily, this);
    renderMessage->SetSubMessageId(SubCommands::SetFontFamily);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void TextProxy::SetText(const std::wstring &text)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(text, this);
    renderMessage->SetSubMessageId(SubCommands::SetText);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

const glm::ivec4 &TextProxy::GetColor()
{
    auto tempData = messageSender.Get(SubCommands::SetColor);
    if(tempData == nullptr)
        return model->GetColor();
    return tempData->GetData<glm::ivec4&>();
}

const std::wstring &TextProxy::GetText()
{
    auto tempData = messageSender.Get(SubCommands::SetText);
    if(tempData == nullptr)
        return model->GetText();
    return tempData->GetData<std::wstring&>();
}

const std::wstring &TextProxy::GetFontFamily()
{
    auto tempData = messageSender.Get(SubCommands::SetFontFamily);
    if(tempData == nullptr)
        return model->GetFontFamily();
    return tempData->GetData<std::wstring&>();
}

FontAlignment TextProxy::GetFontLineAlignment()
{
    return FontAlignmentCenter;
}

FontAlignment TextProxy::GetFontAlignment()
{
    return FontAlignmentCenter;
}

void TextProxy::SetVisible(bool visible)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(visible, this);
    renderMessage->SetSubMessageId(SubCommands::SetVisible);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

bool TextProxy::IsVisible()
{
    auto tempData = messageSender.Get(SubCommands::SetVisible);
    if(tempData == nullptr)
        return model->IsVisible();
    return tempData->GetData<bool>();
}

SubCommands TextProxy::GetModelRequestCommand()
{
    return SubCommands::RequestText;
}

void TextProxy::SetViewportSize(const glm::vec4 &vec4)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(vec4, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortSize);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void TextProxy::SetViewportPosition(const glm::vec4 &vec4)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(vec4, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortPosition);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

glm::vec4 &TextProxy::GetViewportSize()
{
    auto tempData = messageSender.Get(SubCommands::SetViewPortSize);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4&>();
    return model->GetViewportPosition();
}

glm::vec4 &TextProxy::GetViewportPosition()
{
    auto tempData = messageSender.Get(SubCommands::SetViewPortPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4&>();
    return model->GetViewportPosition();
}

void TextProxy::ResetViewport()
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(this);
    renderMessage->SetSubMessageId(SubCommands::ResetViewPort);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}
