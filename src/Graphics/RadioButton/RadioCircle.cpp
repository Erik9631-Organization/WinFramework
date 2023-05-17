//
// Created by erik9 on 4/19/2023.
//

#include "RadioCircle.h"
#include "EventMoveInfo.h"
#include "Presenter.h"
#include "UiElement.h"

void RadioCircle::OnMounted(Presenter &presenter, UiElement &element)
{
    presenter.GetRenderer()->RequestModel(border);
    presenter.GetRenderer()->RequestModel(fill);
    Update();
}

void RadioCircle::OnMove(EventMoveInfo e)
{
    Update();
}

void RadioCircle::OnResize(EventResizeInfo e)
{
    Update();
}

float RadioCircle::GetRelativeZIndex()
{
    return position.z;
}

void RadioCircle::SetRelativeZIndex(float relativeZIndex)
{
    position.z = relativeZIndex;
}

RadioCircle::RadioCircle(UiElement &element) : associatedElement(element), scaler(element.GetAbsolutePosition(), element.GetSize())
{
    element.AddOnMoveSubscriber(*this);
    element.AddOnResizeSubscriber(*this);
    element.AddOnMountedSubscriber(*this);
    element.AddViewportSubscriber(*this);
    border.SetColor({0, 0, 0, 255});
    fill.SetColor({0, 0, 0, 255});
    fill.SetFill(true);
    fill.SetVisible(false);
    UpdateGraphics();
}

float RadioCircle::GetRadius() const
{
    return radius;
}

void RadioCircle::SetRadius(float radius)
{
    this->radius = radius;
    UpdateGraphics();
}

void RadioCircle::SetPadding(float padding)
{
    this->innerCirclePadding = padding;
    UpdateGraphics();
}

float RadioCircle::GetPadding() const
{
    return innerCirclePadding;
}

void RadioCircle::UpdateGraphics()
{
    border.SetSize({radius * 2, radius * 2, 0});
    fill.SetSize({radius * 2 * innerCirclePadding, radius * 2 * innerCirclePadding, 0});
}

ScalingUtil2D &RadioCircle::GetScales()
{
    return scaler;
}

const glm::vec3 & RadioCircle::GetPosition() const
{
    return position;
}

const glm::vec3 & RadioCircle::GetAbsolutePosition() const
{
    return scaler.GetPosition();
}

void RadioCircle::SetPosition(const glm::vec3 &position, bool emit)
{
    auto oldPosition = this->position;
    auto oldAbsolutePosition = GetAbsolutePosition();
    this->position = position;
    if(emit)
        NotifyOnMoveSubscribers(EventMoveInfo(position, GetAbsolutePosition(), this));
}


void RadioCircle::SetTranslate(const glm::vec3 &offset, bool emit)
{

}


const glm::vec3 & RadioCircle::GetTranslate() const
{
    return glm::vec4();
}

void RadioCircle::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.push_back(&subscriber);
}

void RadioCircle::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.erase(std::remove(moveSubscribers.begin(), moveSubscribers.end(), &subscriber), moveSubscribers.end());
}

void RadioCircle::NotifyOnMoveSubscribers(const EventMoveInfo &e)
{
    for(auto &subscriber : moveSubscribers)
        subscriber->OnMove(e);
}

void RadioCircle::SetFillColor(const glm::ivec4 &color)
{
    fill.SetColor(color);
}

void RadioCircle::SetBorderColor(const glm::ivec4 &color)
{
    border.SetColor(color);
}

void RadioCircle::SetFillEnabled(bool state)
{
    fill.SetVisible(state);
}

void RadioCircle::SetVisible(bool state)
{
    border.SetVisible(state);
    fill.SetVisible(state);
}


void RadioCircle::ResetViewport()
{
    border.ResetViewport();
    fill.ResetViewport();
}

void RadioCircle::SetViewportSize(const glm::vec3 &input)
{
    border.SetViewportSize(input);
    fill.SetViewportSize(input);
}

void RadioCircle::SetViewportPosition(const glm::vec3 &input)
{
    border.SetViewportPosition(input);
    fill.SetViewportPosition(input);
}

const glm::vec3 & RadioCircle::GetViewportSize()
{
    return border.GetViewportSize();
}

const glm::vec3 & RadioCircle::GetViewportPosition()
{
    return border.GetViewportPosition();
}

void RadioCircle::AddViewportSubscriber(ViewportSubscriber &subscriber)
{
    border.AddViewportSubscriber(subscriber);
    fill.AddViewportSubscriber(subscriber);
}

void RadioCircle::RemoveViewportSubscriber(ViewportSubscriber &subscriber)
{
    border.RemoveViewportSubscriber(subscriber);
    fill.RemoveViewportSubscriber(subscriber);
}

void RadioCircle::NotifyOnViewportSizeChanged(const ViewportEventInfo &event)
{
    border.NotifyOnViewportSizeChanged(event);
    fill.NotifyOnViewportSizeChanged(event);
}

void RadioCircle::NotifyOnViewportPositionChanged(const ViewportEventInfo &event)
{
    border.NotifyOnViewportPositionChanged(event);
    fill.NotifyOnViewportPositionChanged(event);
}

bool RadioCircle::IsViewportSet() const
{
    return border.IsViewportSet();
}

void RadioCircle::NotifyOnViewportReset(const ViewportEventInfo &event)
{
    border.NotifyOnViewportReset(event);
    fill.NotifyOnViewportReset(event);
}

void RadioCircle::OnViewportSizeChanged(const ViewportEventInfo &event)
{
    border.SetViewportSize(event.GetSize());
    fill.SetViewportSize(event.GetSize());
}

void RadioCircle::OnViewportPositionChanged(const ViewportEventInfo &event)
{
    border.SetViewportPosition(event.GetPosition());
    fill.SetViewportPosition(event.GetPosition());
}

void RadioCircle::OnViewportReset(const ViewportEventInfo &event)
{
    border.ResetViewport();
    fill.ResetViewport();
}

RadioCircle::~RadioCircle()
{
    associatedElement.RemoveOnMoveSubscriber(*this);
    associatedElement.RemoveOnResizeSubscriber(*this);
    associatedElement.RemoveOnMountedSubscriber(*this);
    associatedElement.RemoveViewportSubscriber(*this);
}

void RadioCircle::Update()
{
    scaler.Scale(position);
    border.SetPosition(scaler.GetPosition() + position);
    fill.SetPosition(scaler.GetPosition() + position);
}
