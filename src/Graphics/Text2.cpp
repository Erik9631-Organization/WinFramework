//
// Created by erik9 on 4/4/2023.
//

#include "Text2.h"
#include "Presenter.h"
#include "EventMoveInfo.h"
#include "DefaultRelativeZIndex.h"
#include "UiElement.h"

void Text2::OnMounted(Presenter &presenter, UiElement &element)
{
    this->presenter = &presenter;
    this->parentElement = &element;
    presenter.GetRenderer()->RequestModel(textProxy);
}

void Text2::OnMove(EventMoveInfo e)
{
    textScaler.Scale(textPosition);
    textProxy.SetPosition(textScaler.GetPosition());
}

void Text2::OnResize(EventResizeInfo e)
{
    textScaler.Scale(textPosition);
    textProxy.SetPosition(textScaler.GetPosition());
}

float Text2::GetRelativeZIndex()
{
    return this->textPosition.z;
}

void Text2::SetRelativeZIndex(float relativeZIndex)
{
    this->textPosition.z = relativeZIndex;
}


void Text2::SetFontSize(float fontSize)
{
    textProxy.SetFontSize(fontSize);
}

void Text2::SetFontAlignment(FontAlignment alignment)
{
    textProxy.SetFontAlignment(alignment);
}

void Text2::SetFontLineAlignment(FontAlignment alignment)
{
    textProxy.SetFontLineAlignment(alignment);
}

void Text2::SetColor(const glm::ivec4 &color)
{
    textProxy.SetColor(color);
}

void Text2::SetFontFamily(const std::wstring &fontFamily)
{
    textProxy.SetFontFamily(fontFamily);
}

const glm::ivec4 &Text2::GetColor()
{
    return textProxy.GetColor();
}

const std::wstring &Text2::GetText()
{
    return textProxy.GetText();
}

const std::wstring &Text2::GetFontFamily()
{
    return textProxy.GetFontFamily();
}

FontAlignment Text2::GetFontLineAlignment()
{
    return textProxy.GetFontLineAlignment();
}

FontAlignment Text2::GetFontAlignment()
{
    return textProxy.GetFontAlignment();
}

void Text2::SetText(const std::wstring &text)
{
    textProxy.SetText(text);
}

Text2::Text2(UiElement *associatedElement) : textScaler(associatedElement->GetAbsolutePosition(), associatedElement->GetSize())
{
    parentElement = associatedElement;
    associatedElement->AddOnMountedSubscriber(*this);
    associatedElement->AddOnMoveSubscriber(*this);
    associatedElement->AddOnResizeSubscriber(*this);
    textScaler.SetCalculateFromCenterY(true);
    textScaler.SetCalculateFromCenterX(true);
    textProxy.SetColor({0, 0, 0, 255});
}

Text2::~Text2()
{
    this->parentElement->RemoveOnMountedSubscriber(*this);
    this->parentElement->RemoveOnMoveSubscriber(*this);
}

glm::vec4 Text2::GetPosition()
{

    return glm::vec4();
}

float Text2::GetX()
{
    return textPosition.x;
}

float Text2::GetY()
{
    return textPosition.y;
}

float Text2::GetZ()
{
    return textPosition.z;
}

float Text2::GetW()
{
    return textPosition.w;
}

float Text2::GetAbsoluteX()
{
    return textPosition.x;
}

float Text2::GetAbsoluteY()
{
    return textPosition.y;
}

const glm::vec4 &Text2::GetAbsolutePosition()
{
    return textPosition;
}

void Text2::SetPosition(glm::vec4 position, bool emit)
{
    if(emit)
        NotifyOnMoveSubscribers(EventMoveInfo(position, textPosition, this));
    textPosition = position;
    OnMove(EventMoveInfo(position, textPosition, this));
}

void Text2::SetPosition(glm::vec4 position)
{
    SetPosition(position, true);
}

void Text2::SetPosition(float x, float y, float z, float w, bool emit)
{
    SetPosition(glm::vec4(x, y, z, w), emit);
}

void Text2::SetPosition(float x, float y, float z, float w)
{
    SetPosition(glm::vec4(x, y, z, w), true);
}

void Text2::SetX(float x, bool emit)
{
    SetPosition({x, textPosition.y, textPosition.z, textPosition.w}, emit);
}

void Text2::SetX(float x)
{
    SetPosition({x, textPosition.y, textPosition.z, textPosition.w}, true);
}

void Text2::SetY(float y, bool emit)
{
    SetPosition({textPosition.x, y, textPosition.z, textPosition.w}, emit);
}

void Text2::SetY(float y)
{
    SetPosition({textPosition.x, y, textPosition.z, textPosition.w}, true);
}

void Text2::SetZ(float z, bool emit)
{
    SetPosition({textPosition.x, textPosition.y, z, textPosition.w}, emit);
}

void Text2::SetZ(float z)
{
    SetPosition({textPosition.x, textPosition.y, z, textPosition.w}, true);
}

void Text2::SetW(float w, bool emit)
{
    SetPosition({textPosition.x, textPosition.y, textPosition.z, w}, emit);
}

void Text2::SetW(float w)
{
    SetPosition({textPosition.x, textPosition.y, textPosition.z, w}, true);
}

void Text2::SetTranslate(glm::vec4 offset, bool emit)
{

}

void Text2::SetTranslate(glm::vec4 offset)
{

}

void Text2::SetTranslateX(float x, bool emit)
{

}

void Text2::SetTranslateX(float x)
{

}

void Text2::SetTranslateY(float y, bool emit)
{

}

void Text2::SetTranslateY(float y)
{

}

glm::vec4 Text2::GetTranslate()
{
    return glm::vec4();
}

float Text2::GetTranslateX()
{
    return 0;
}

float Text2::GetTranslateY()
{
    return 0;
}

void Text2::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.push_back(&subscriber);
}

void Text2::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.erase(std::remove(moveSubscribers.begin(), moveSubscribers.end(), &subscriber), moveSubscribers.end());
}

void Text2::NotifyOnMoveSubscribers(EventMoveInfo e)
{
    for(auto &subscriber : moveSubscribers)
        subscriber->OnMove(e);
}

ScalingUtil2D &Text2::GetScales()
{
    return textScaler;
}

void Text2::SetVisible(bool state)
{
    textProxy.SetVisible(state);
}
