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
}

void RadioCircle::OnMove(EventMoveInfo e)
{
    scaler.Scale(position);
    border.SetPosition(scaler.GetPosition() + position);
    fill.SetPosition(scaler.GetPosition() + position);
}

void RadioCircle::OnResize(EventResizeInfo e)
{
    scaler.Scale(position);
    border.SetPosition(scaler.GetPosition() + position);
    fill.SetPosition(scaler.GetPosition() + position);
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
    this->position = position;
    if(emit)
        NotifyOnMoveSubscribers(EventMoveInfo(position, position, this));
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

void RadioCircle::NotifyOnMoveSubscribers(EventMoveInfo e)
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


void RadioCircle::ResetViewPort()
{
    border.ResetViewPort();
    fill.ResetViewPort();
}

void RadioCircle::SetViewPortSize(const glm::vec4 &vec4)
{
    border.SetViewPortSize(vec4);
    fill.SetViewPortSize(vec4);
}

void RadioCircle::SetViewPortPosition(const glm::vec4 &vec4)
{
    border.SetViewPortPosition(vec4);
    fill.SetViewPortPosition(vec4);
}

glm::vec4 &RadioCircle::GetViewPortSize()
{
    return border.GetViewPortSize();
}

glm::vec4 &RadioCircle::GetViewPortPosition()
{
    return border.GetViewPortPosition();
}
