//
// Created by erik9 on 2/21/2023.
//

#include "TextModel.h"
#include "Renderer.h"

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

glm::vec4 TextModel::GetAbsolutePosition()
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
        case SubCommands::SetPosition:
            SetPosition(message->GetData<glm::vec4>());
            break;
        case SubCommands::SetTranslate:
            SetTranslate(message->GetData<glm::vec4>());
        case SubCommands::SetTranslateX:
            SetTranslateX(message->GetData<float>());
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
        case SubCommands::SetColor:
            SetColor(message->GetData<glm::vec4>());
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
    if(renderer == nullptr)
        return;

    auto api = renderer->AcquireRenderingApi();
    api->SetColor(color);
    if(viewPort.IsSet());
        api->SetClippingRectangle(viewPort.GetViewPortPosition(), viewPort.GetViewPortSize());

    api->SetFontSize(fontSize);
    api->SetFontFamily(fontFamily);
    api->SetFontFamily(fontFamily);
    api->DrawString(text, movableModelBehavior.GetPosition(), format);
}

void TextModel::SetRenderingProvider(Renderer *renderer)
{
    this->renderer = renderer;
}

void TextModel::SetAssociatedModelId(unsigned long long int id)
{
    this->modelId = id;
}

size_t &TextModel::GetModelId()
{
    return modelId;
}

void TextModel::SetColor(const glm::vec4 &color)
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
