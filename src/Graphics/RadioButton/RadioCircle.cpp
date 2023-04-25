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
    element.AddViewport2Subscriber(*this);
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
    border.SetSize({radius * 2, radius * 2, 0, 0});
    fill.SetSize({radius * 2 * innerCirclePadding, radius * 2 * innerCirclePadding, 0, 0});
}

ScalingUtil2D &RadioCircle::GetScales()
{
    return scaler;
}

glm::vec4 RadioCircle::GetPosition()
{
    return position;
}

float RadioCircle::GetX()
{
    return position.x;
}

float RadioCircle::GetY()
{
    return position.y;
}

float RadioCircle::GetZ()
{
    return position.z;
}

float RadioCircle::GetW()
{
    return position.w;
}

float RadioCircle::GetAbsoluteX()
{
    scaler.Scale(position);
    return scaler.GetX();
}

float RadioCircle::GetAbsoluteY()
{
    scaler.Scale(position);
    return scaler.GetY();
}

const glm::vec4 &RadioCircle::GetAbsolutePosition()
{
    scaler.Scale(position);
    return scaler.GetPosition();
}

void RadioCircle::SetPosition(glm::vec4 position, bool emit)
{
    auto oldPosition = this->position;
    auto oldAbsolutePosition = GetAbsolutePosition();
    this->position = position;
    if(emit)
        NotifyOnMoveSubscribers(EventMoveInfo(position, GetAbsolutePosition(), this));
}

void RadioCircle::SetPosition(glm::vec4 position)
{
    SetPosition(position, true);
}

void RadioCircle::SetPosition(float x, float y, float z, float w, bool emit)
{
    SetPosition({x, y, z, w}, emit);
}

void RadioCircle::SetPosition(float x, float y, float z, float w)
{
    SetPosition({x, y, z, w}, true);
}

void RadioCircle::SetX(float x, bool emit)
{
    SetPosition({x, 0, 0, 1}, emit);
}

void RadioCircle::SetX(float x)
{
    SetPosition({x, position.y, position.z, position.w}, true);
}

void RadioCircle::SetY(float y, bool emit)
{
    SetPosition({position.x, y, position.z, position.w}, emit);
}

void RadioCircle::SetY(float y)
{
    SetPosition({position.x, y, position.z, position.w}, true);
}

void RadioCircle::SetZ(float z, bool emit)
{
    SetPosition({position.x, position.y, z, position.w}, emit);
}

void RadioCircle::SetZ(float z)
{
    SetPosition({position.x, position.y, z, position.w}, true);
}

void RadioCircle::SetW(float w, bool emit)
{
    SetPosition({position.x, position.y, position.z, w}, emit);
}

void RadioCircle::SetW(float w)
{
    SetPosition({position.x, position.y, position.z, w}, true);
}

void RadioCircle::SetTranslate(glm::vec4 offset, bool emit)
{

}

void RadioCircle::SetTranslate(glm::vec4 offset)
{

}

void RadioCircle::SetTranslateX(float x, bool emit)
{

}

void RadioCircle::SetTranslateX(float x)
{

}

void RadioCircle::SetTranslateY(float y, bool emit)
{

}

void RadioCircle::SetTranslateY(float y)
{

}

glm::vec4 RadioCircle::GetTranslate()
{
    return glm::vec4();
}

float RadioCircle::GetTranslateX()
{
    return 0;
}

float RadioCircle::GetTranslateY()
{
    return 0;
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

void RadioCircle::SetViewportSize(const glm::vec4 &vec4)
{
    border.SetViewportSize(vec4);
    fill.SetViewportSize(vec4);
}

void RadioCircle::SetViewportPosition(const glm::vec4 &vec4)
{
    border.SetViewportPosition(vec4);
    fill.SetViewportPosition(vec4);
}

const glm::vec4 & RadioCircle::GetViewportSize()
{
    return border.GetViewportSize();
}

const glm::vec4 & RadioCircle::GetViewportPosition()
{
    return border.GetViewportPosition();
}

void RadioCircle::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    border.AddViewport2Subscriber(subscriber);
    fill.AddViewport2Subscriber(subscriber);
}

void RadioCircle::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    border.RemoveViewport2Subscriber(subscriber);
    fill.RemoveViewport2Subscriber(subscriber);
}

void RadioCircle::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    border.NotifyOnViewportSizeChanged(event);
    fill.NotifyOnViewportSizeChanged(event);
}

void RadioCircle::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    border.NotifyOnViewportPositionChanged(event);
    fill.NotifyOnViewportPositionChanged(event);
}

bool RadioCircle::IsViewportSet() const
{
    return border.IsViewportSet();
}

void RadioCircle::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    border.NotifyOnViewportReset(event);
    fill.NotifyOnViewportReset(event);
}

void RadioCircle::OnViewportSizeChanged(const Viewport2EventInfo &event)
{
    border.SetViewportSize(event.GetSize());
    fill.SetViewportSize(event.GetSize());
}

void RadioCircle::OnViewportPositionChanged(const Viewport2EventInfo &event)
{
    border.SetViewportPosition(event.GetPosition());
    fill.SetViewportPosition(event.GetPosition());
}

void RadioCircle::OnViewportReset(const Viewport2EventInfo &event)
{
    border.ResetViewport();
    fill.ResetViewport();
}

RadioCircle::~RadioCircle()
{
    associatedElement.RemoveOnMoveSubscriber(*this);
    associatedElement.RemoveOnResizeSubscriber(*this);
    associatedElement.RemoveOnMountedSubscriber(*this);
    associatedElement.RemoveViewport2Subscriber(*this);
}

void RadioCircle::Update()
{
    scaler.Scale(position);
    border.SetPosition(scaler.GetPosition() + position);
    fill.SetPosition(scaler.GetPosition() + position);
}
