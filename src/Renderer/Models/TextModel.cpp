//
// Created by erik9 on 2/21/2023.
//

#include "TextModel.h"
#include "Renderer.h"
#include "EventMoveInfo.h"

const glm::vec3 & TextModel::GetPosition() const
{
    return movableModelBehavior.GetPosition();
}

const glm::vec3 & TextModel::GetAbsolutePosition() const
{
    return movableModelBehavior.GetAbsolutePosition();
}

void TextModel::SetPosition(const glm::vec3 &position, bool emit)
{
    movableModelBehavior.SetPosition(position, emit);
}

void TextModel::SetTranslate(const glm::vec3 &offset, bool emit)
{
    movableModelBehavior.SetTranslate(offset, emit);
}

const glm::vec3 & TextModel::GetTranslate() const
{
    return movableModelBehavior.GetTranslate();
}

void TextModel::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    switch(message->GetSubMessageId())
    {
        case SubCommands::SetViewPortSize:
            SetViewportSize(message->GetData<glm::vec4>());
            break;
        case SubCommands::SetViewPortPosition:
            SetViewportPosition(message->GetData<glm::vec3>());
            break;
        case SubCommands::SetPosition:
            SetPosition(message->GetData<glm::vec3>());
            break;
        case SubCommands::SetTranslate:
            SetTranslate(message->GetData<glm::vec3>());
            break;
        case SubCommands::SetFontSize:
            SetFontSize(message->GetData<float>());
            break;
        case SubCommands::SetFontAlignment:
            SetFontAlignment(message->GetData<FontAlignment>());
            break;
        case SubCommands::SetFontLineAlignment:
            SetFontLineAlignment(message->GetData<FontAlignment>());
            break;
        case SubCommands::SetColor:
            SetColor(message->GetData<glm::ivec4>());
            break;
        case SubCommands::SetText:
            SetText(message->GetData<std::wstring>());
            break;
        case SubCommands::SetFontFamily:
            SetFontFamily(message->GetData<std::wstring>());
            break;
        case SubCommands::SetVisible:
            SetVisible(message->GetData<bool>());
            break;
        default:
            break;
    }
}

void TextModel::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    movableModelBehavior.AddOnMoveSubscriber(subscriber);
}

void TextModel::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{
    movableModelBehavior.AddOnMoveSubscriber(subscriber);
}

float TextModel::GetZIndex()
{
    return movableModelBehavior.GetPosition().z;
}

void TextModel::Draw()
{
    if(!visible)
        return;

    if(renderer == nullptr)
        return;

    auto api = renderer->AcquireRenderingApi();
    auto format = api->CreateFontFormat();
    format->SetAlignment(fontAlignment);
    format->SetLineAlignment(fontLineAlignment);
    api->SetColor(color);
    if(viewPort.IsViewportSet())
        api->SetClippingRectangle(viewPort.GetViewportPosition(), viewPort.GetViewportSize());

    api->SetFontSize(fontSize);
    api->SetFontFamily(fontFamily);
    api->DrawString(text, movableModelBehavior.GetPosition(), *format);
}

void TextModel::SetRenderer(Renderer *renderer)
{
    this->renderer = renderer;
}
void TextModel::SetModelId(size_t id)
{
    this->modelId = id;
}

const size_t & TextModel::GetModelId()
{
    return modelId;
}

void TextModel::SetColor(const glm::ivec4 &color)
{
    this->color = color;
}

const glm::ivec4 &TextModel::GetColor()
{
    return this->color;
}

void TextModel::SetFontSize(float fontSize)
{
    this->fontSize = fontSize;
}

void TextModel::SetFontAlignment(FontAlignment alignment)
{
    this->fontAlignment = alignment;
}

void TextModel::SetFontLineAlignment(FontAlignment alignment)
{
    this->fontLineAlignment = alignment;
}

void TextModel::NotifyOnMoveSubscribers(const EventMoveInfo &e)
{
    movableModelBehavior.NotifyOnMoveSubscribers(e);
}

void TextModel::SetText(const std::wstring &text)
{
    this->text = text;
}

void TextModel::SetFontFamily(const std::wstring &fontFamily)
{
    this->fontFamily = fontFamily;
}

const std::wstring &TextModel::GetText()
{
    return text;
}

const std::wstring &TextModel::GetFontFamily()
{
    return this->fontFamily;
}

FontAlignment TextModel::GetFontLineAlignment()
{
    return fontLineAlignment;
}

FontAlignment TextModel::GetFontAlignment()
{
    return fontAlignment;
}

TextModel::TextModel() : movableModelBehavior(*this)
{

}

void TextModel::SetVisible(bool visible)
{
    this->visible = visible;
}

bool TextModel::IsVisible()
{
    return visible;
}

void TextModel::SetViewportSize(const glm::vec4 &vec4)
{
    viewPort.SetViewportSize(vec4);
    viewPort.NotifyOnViewportSizeChanged({GetViewportPosition(), vec4, this});
}

void TextModel::SetViewportPosition(const glm::vec3 &input)
{
    viewPort.SetViewportPosition(input);
    NotifyOnViewportPositionChanged({input, GetViewportSize(), this});
}

const glm::vec4 & TextModel::GetViewportSize()
{
    return viewPort.GetViewportSize();
}

const glm::vec3 & TextModel::GetViewportPosition()
{
    return viewPort.GetViewportPosition();
}

void TextModel::ResetViewport()
{
    viewPort.ResetViewport();
}

void TextModel::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPort.AddViewport2Subscriber(subscriber);
}

void TextModel::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewPort.RemoveViewport2Subscriber(subscriber);
}

void TextModel::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportSizeChanged(event);
}

void TextModel::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportPositionChanged(event);
}

bool TextModel::IsViewportSet() const
{
    return viewPort.IsViewportSet();
}

void TextModel::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    viewPort.NotifyOnViewportReset(event);
}
