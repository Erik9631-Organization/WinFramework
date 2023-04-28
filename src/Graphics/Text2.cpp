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
    presenter.GetRenderer()->RequestModel(textProxy);
    textScaler.Scale(textPosition);
    textProxy.SetPosition(textScaler.GetPosition());
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

Text2::Text2(UiElement &associatedElement) : textScaler(associatedElement.GetAbsolutePosition(), associatedElement.GetSize()),
                                             associatedElement(associatedElement)
{
    associatedElement.AddOnMountedSubscriber(*this);
    associatedElement.AddOnMoveSubscriber(*this);
    associatedElement.AddOnResizeSubscriber(*this);
    associatedElement.AddViewport2Subscriber(*this);
    textScaler.SetCalculateFromCenterY(true);
    textScaler.SetCalculateFromCenterX(true);
    textProxy.SetColor({0, 0, 0, 255});

}

Text2::~Text2()
{
    associatedElement.RemoveOnMountedSubscriber(*this);
    associatedElement.RemoveOnMoveSubscriber(*this);
    associatedElement.RemoveOnResizeSubscriber(*this);
    associatedElement.RemoveViewport2Subscriber(*this);
}

const glm::vec4 & Text2::GetPosition() const
{
    return textPosition;
}

const glm::vec4 &Text2::GetAbsolutePosition() const
{
    return textScaler.GetPosition();
}

void Text2::SetPosition(const glm::vec4 &position, bool emit)
{
    textPosition = position;
    if(emit)
        NotifyOnMoveSubscribers(EventMoveInfo(position, GetAbsolutePosition(), this));
    OnMove(EventMoveInfo(EventMoveInfo(position, GetAbsolutePosition(), this)));
}

void Text2::SetTranslate(const glm::vec4 &offset, bool emit)
{

}


const glm::vec4 & Text2::GetTranslate() const
{
    return glm::vec4();
}


void Text2::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.push_back(&subscriber);
}

void Text2::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.erase(std::remove(moveSubscribers.begin(), moveSubscribers.end(), &subscriber), moveSubscribers.end());
}

void Text2::NotifyOnMoveSubscribers(const EventMoveInfo &e)
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


void Text2::ResetViewport()
{
    textProxy.ResetViewport();
}

void Text2::SetViewportSize(const glm::vec4 &vec4)
{
    textProxy.SetViewportSize(vec4);
}

void Text2::SetViewportPosition(const glm::vec4 &vec4)
{
    textProxy.SetViewportPosition(vec4);
}

const glm::vec4 & Text2::GetViewportSize()
{
    return textProxy.GetViewportSize();
}

const glm::vec4 & Text2::GetViewportPosition()
{
    return textProxy.GetViewportPosition();
}

void Text2::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    textProxy.AddViewport2Subscriber(subscriber);
}

void Text2::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    textProxy.RemoveViewport2Subscriber(subscriber);
}

void Text2::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    textProxy.NotifyOnViewportSizeChanged(event);
}

void Text2::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    textProxy.NotifyOnViewportPositionChanged(event);
}

bool Text2::IsViewportSet() const
{
    return textProxy.IsViewportSet();
}

void Text2::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    textProxy.NotifyOnViewportReset(event);
}

void Text2::OnViewportSizeChanged(const Viewport2EventInfo &event)
{
    textProxy.SetViewportSize(event.GetSize());
}

void Text2::OnViewportPositionChanged(const Viewport2EventInfo &event)
{
    textProxy.SetViewportPosition(event.GetPosition());
}

void Text2::OnViewportReset(const Viewport2EventInfo &event)
{
    textProxy.ResetViewport();
}
