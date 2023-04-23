//
// Created by erik9 on 2/21/2023.
//

#include "TextModel.h"
#include "Renderer.h"
#include "EventMoveInfo.h"

glm::vec4 TextModel::GetPosition()
{
    return movableModelBehavior.GetPosition();
}

float TextModel::GetX()
{
    return movableModelBehavior.GetX();
}

float TextModel::GetY()
{
    return movableModelBehavior.GetY();
}

float TextModel::GetZ()
{
    return movableModelBehavior.GetZ();
}

float TextModel::GetW()
{
    return movableModelBehavior.GetW();
}

float TextModel::GetAbsoluteX()
{
    return movableModelBehavior.GetAbsoluteX();
}

float TextModel::GetAbsoluteY()
{
    return movableModelBehavior.GetAbsoluteY();
}

const glm::vec4 & TextModel::GetAbsolutePosition()
{
    return movableModelBehavior.GetAbsolutePosition();
}

void TextModel::SetPosition(glm::vec4 position, bool emit)
{
    movableModelBehavior.SetPosition(position, emit);
}

void TextModel::SetPosition(glm::vec4 position)
{
    movableModelBehavior.SetPosition(position);
}

void TextModel::SetPosition(float x, float y, float z, float w, bool emit)
{
    movableModelBehavior.SetPosition(x, y, z, w, emit);
}

void TextModel::SetPosition(float x, float y, float z, float w)
{
    movableModelBehavior.SetPosition(x, y, z, w);
}

void TextModel::SetX(float x, bool emit)
{
    movableModelBehavior.SetX(x, emit);
}

void TextModel::SetX(float x)
{
    movableModelBehavior.SetX(x);
}

void TextModel::SetY(float y, bool emit)
{
    movableModelBehavior.SetY(y, emit);
}

void TextModel::SetY(float y)
{
    movableModelBehavior.SetY(y);
}

void TextModel::SetZ(float z, bool emit)
{
    movableModelBehavior.SetZ(z, emit);
}

void TextModel::SetZ(float z)
{
    movableModelBehavior.SetZ(z);
}

void TextModel::SetW(float w, bool emit)
{
    movableModelBehavior.SetW(w, emit);
}

void TextModel::SetW(float w)
{
    movableModelBehavior.SetW(w);
}

void TextModel::SetTranslate(glm::vec4 offset, bool emit)
{
    movableModelBehavior.SetTranslate(offset, emit);
}

void TextModel::SetTranslate(glm::vec4 offset)
{
    movableModelBehavior.SetTranslate(offset);
}

void TextModel::SetTranslateX(float x, bool emit)
{
    movableModelBehavior.SetTranslateX(x, emit);
}

void TextModel::SetTranslateX(float x)
{
    movableModelBehavior.SetTranslateX(x);
}

void TextModel::SetTranslateY(float y, bool emit)
{
    movableModelBehavior.SetTranslateY(y, emit);
}

void TextModel::SetTranslateY(float y)
{
    movableModelBehavior.SetTranslateY(y);
}

glm::vec4 TextModel::GetTranslate()
{
    return movableModelBehavior.GetTranslate();
}

float TextModel::GetTranslateX()
{
    return movableModelBehavior.GetTranslateX();
}

float TextModel::GetTranslateY()
{
    return movableModelBehavior.GetTranslateY();
}

void TextModel::ReceiveCommand(std::unique_ptr<RenderMessage> message)
{
    switch(message->GetSubMessageId())
    {
        case SubCommands::SetX:
            SetX(message->GetData<float>());
            break;
        case SubCommands::SetY:
            SetY(message->GetData<float>());
            break;
        case SubCommands::SetViewPortSize:
            SetViewportSize(message->GetData<glm::vec4>());
            break;
        case SubCommands::SetViewPortPosition:
            SetViewportPosition(message->GetData<glm::vec4>());
            break;
        case SubCommands::SetPosition:
            SetPosition(message->GetData<glm::vec4>());
            break;
        case SubCommands::SetTranslate:
            SetTranslate(message->GetData<glm::vec4>());
            break;
        case SubCommands::SetTranslateX:
            SetTranslateX(message->GetData<float>());
            break;
        case SubCommands::SetTranslateY:
            SetTranslateY(message->GetData<float>());
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
    return movableModelBehavior.GetZ();
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
void TextModel::SetModelId(long long int id)
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

void TextModel::NotifyOnMoveSubscribers(EventMoveInfo e)
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
    viewPort.NotifyOnViewportSizeChanged({vec4, GetViewportPosition(), this});
}

void TextModel::SetViewportPosition(const glm::vec4 &vec4)
{
    viewPort.SetViewportPosition(vec4);
    NotifyOnViewportPositionChanged({vec4, GetViewportPosition(), this});
}

glm::vec4 &TextModel::GetViewportSize()
{
    return viewPort.GetViewportSize();
}

glm::vec4 &TextModel::GetViewportPosition()
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
