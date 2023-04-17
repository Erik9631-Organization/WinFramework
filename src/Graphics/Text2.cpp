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
    presenter.GetRenderer()->RequestModel(SubCommands::RequestText, textProxy);
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
}

Text2::~Text2()
{
    this->parentElement->RemoveOnMountedSubscriber(*this);
    this->parentElement->RemoveOnMoveSubscriber(*this);
}
