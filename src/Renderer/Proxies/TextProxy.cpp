//
// Created by erik9 on 12/11/2022.
//

#include "TextProxy.h"
#include "EventMoveInfo.h"
#include "TextModel.h"
#include <iostream>

std::wstring TextProxy::defaultText = L"";

const glm::vec4 & TextProxy::GetPosition() const
{
    auto tempData = messageSender.Get(SubCommands::SetPosition);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec4&>();
    if(model == nullptr)
        return defaultVec;
    return model->GetPosition();
}

const glm::vec4 & TextProxy::GetAbsolutePosition() const
{
    return model->GetAbsolutePosition();
}

void TextProxy::SetPosition(const glm::vec4 &position, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(position, this);
    renderMessage->SetSubMessageId(SubCommands::SetPosition);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

void TextProxy::SetTranslate(const glm::vec4 &offset, bool emit)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(offset, this);
    renderMessage->SetSubMessageId(SubCommands::SetTranslate);
    messageSender.SendRenderingMessage(std::move(renderMessage));
}

const glm::vec4 & TextProxy::GetTranslate() const
{
    auto tempData = messageSender.Get(SubCommands::SetTranslate);
    if(tempData != nullptr)
        return tempData->GetData<const glm::vec4&>();
    if(model == nullptr)
        return defaultVec;

    return model->GetTranslate();
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

void TextProxy::NotifyOnMoveSubscribers(const EventMoveInfo &e)
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
    if(tempData != nullptr)
        return tempData->GetData<glm::ivec4&>();
    if(model == nullptr)
        return defaultColorVec;

    return model->GetColor();
}

const std::wstring &TextProxy::GetText()
{
    auto tempData = messageSender.Get(SubCommands::SetText);
    if(tempData != nullptr)
        return tempData->GetData<std::wstring&>();
    if(model == nullptr)
        return defaultText;
    return model->GetText();
}

const std::wstring &TextProxy::GetFontFamily()
{
    auto tempData = messageSender.Get(SubCommands::SetFontFamily);
    if(tempData != nullptr)
        return tempData->GetData<std::wstring&>();
    if(model == nullptr)
        return defaultText;
    return model->GetFontFamily();
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
    if(tempData != nullptr)
        return tempData->GetData<bool>();
    if (model == nullptr)
        return false;
    return model->IsVisible();
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
    NotifyOnViewportSizeChanged({GetViewportPosition(), vec4, this});
}

void TextProxy::SetViewportPosition(const glm::vec4 &vec4)
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(vec4, this);
    renderMessage->SetSubMessageId(SubCommands::SetViewPortPosition);
    messageSender.SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportPositionChanged({vec4, GetViewportPosition(), this});
}

const glm::vec4 & TextProxy::GetViewportSize()
{
    auto tempData = messageSender.Get(SubCommands::SetViewPortSize);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4&>();
    if(model == nullptr)
        return defaultVec;
    return model->GetViewportPosition();
}

const glm::vec4 & TextProxy::GetViewportPosition()
{
    auto tempData = messageSender.Get(SubCommands::SetViewPortPosition);
    if(tempData != nullptr)
        return tempData->GetData<glm::vec4&>();
    if(model == nullptr)
        return defaultVec;
    return model->GetViewportPosition();
}

void TextProxy::ResetViewport()
{
    auto renderMessage = RenderMessage::CreatePropertyMessage(this);
    renderMessage->SetSubMessageId(SubCommands::ResetViewPort);
    messageSender.SendRenderingMessage(std::move(renderMessage));
    NotifyOnViewportReset({GetViewportPosition(), GetViewportSize(), this});
}

void TextProxy::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPortSubscribers.push_back(&subscriber);
}

void TextProxy::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPortSubscribers.erase(std::remove(viewPortSubscribers.begin(), viewPortSubscribers.end(), &subscriber), viewPortSubscribers.end());
}

void TextProxy::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    for(auto i : viewPortSubscribers)
        i->OnViewportSizeChanged(event);
}

void TextProxy::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    for(auto i : viewPortSubscribers)
        i->OnViewportPositionChanged(event);
}

bool TextProxy::IsViewportSet() const
{
    return model->IsViewportSet();
}

void TextProxy::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    for(auto i : viewPortSubscribers)
        i->OnViewportReset(event);
}
