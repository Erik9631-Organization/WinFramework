#include "Viewport.h"
#include "EventTypes/EventMoveInfo.h"
#include "EventTypes/EventResizeInfo.h"
#include "Components/UiElement.h"
#include "EventTypes/EventUpdateInfo.h"

void Viewport::CalculateAbsolutePosition(const glm::vec2 &relative)
{
    absolutePosition.x = (relative.x + associatedAdjustable.GetAbsoluteX()) * xMultiplier;
    absolutePosition.y = (relative.y + associatedAdjustable.GetAbsoluteY()) * yMultiplier;
}

void Viewport::CalculateAbsoluteSize(const glm::vec2 &size)
{
    absoluteSize.x = (size.x+ associatedAdjustable.GetWidth() + 1) * widthMultiplier;
    absoluteSize.y = (size.y + associatedAdjustable.GetHeight() + 1) * heightMultiplier;
}

Viewport::Viewport(Adjustable& adjustable) : associatedAdjustable(adjustable), viewportNode((Adjustable*)this), moveBehavior(viewportNode), resizeBehavior(*this)
{

    CalculateAbsoluteSize({0, 0});
    CalculateAbsolutePosition({0, 0});
    internalOffset = {0, 0};
}


void Viewport::SetXMultiplier(float x)
{
    xMultiplier = x;
}

void Viewport::SetYMultiplier(float y)
{
    yMultiplier = y;
}

void Viewport::SetWidthMultiplier(float width)
{
    widthMultiplier = width;
}

void Viewport::SetHeightMultiplier(float height)
{
    heightMultiplier = height;
}

float Viewport::GetViewportXMultiplier()
{
    return xMultiplier;
}

float Viewport::GetViewportYMultiplier()
{
    return yMultiplier;
}

float Viewport::GetViewportWidthMultiplier()
{
    return widthMultiplier;
}

float Viewport::GetViewportHeightMultiplier()
{
    return heightMultiplier;
}

int Viewport::GetViewportAbsoluteWidth()
{
    return absoluteSize.x;
}

int Viewport::GetViewportAbsoluteHeight()
{
    return absoluteSize.y;
}

glm::vec2 Viewport::GetViewportAbsoluteSize()
{
    return absoluteSize;
}

void Viewport::AddOnMoveSubscriber(MoveSubscriber& subscriber)
{
    moveBehavior.AddOnMoveSubscriber(subscriber);
}

void Viewport::RemoveOnMoveSubscriber(MoveSubscriber& subscriber)
{
    moveBehavior.RemoveOnMoveSubscriber(subscriber);
}

void Viewport::NotifyOnMoveSubscribers(EventMoveInfo event)
{
    moveBehavior.NotifyOnMoveSubscribers(event);
}

glm::vec2 Viewport::GetPosition()
{
    return moveBehavior.GetPosition();
}

float Viewport::GetX()
{
    return moveBehavior.GetX();
}

float Viewport::GetY()
{
    return moveBehavior.GetY();
}

float Viewport::GetAbsoluteX()
{
    return absolutePosition.x;
}

float Viewport::GetAbsoluteY()
{
    return absolutePosition.y;
}

glm::vec2 Viewport::GetAbsolutePosition()
{
    return absolutePosition;
}

void Viewport::SetPosition(const glm::vec2 &position)
{
    moveBehavior.SetPosition(position);
}

void Viewport::SetPosition(float x, float y)
{
    moveBehavior.SetPosition(x, y);
}

void Viewport::SetX(float x)
{
    moveBehavior.SetX(x);
}

void Viewport::SetY(float y)
{
    moveBehavior.SetY(y);
}

void Viewport::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    resizeBehavior.NotifyOnResizeSubscribers(event);
}

void Viewport::AddOnResizeSubscriber(ResizeSubscriber& subscriber)
{
    resizeBehavior.AddOnResizeSubscriber(subscriber);
}

void Viewport::RemoveOnResizeSubscriber(ResizeSubscriber& subscriber)
{
    resizeBehavior.RemoveOnResizeSubscriber(subscriber);
}

glm::vec2 Viewport::GetSize()
{
    return resizeBehavior.GetSize();
}

float Viewport::GetWidth()
{
    return resizeBehavior.GetWidth();
}

float Viewport::GetHeight()
{
    return resizeBehavior.GetHeight();
}

void Viewport::SetSize(const glm::vec2 &size, bool emit)
{
    resizeBehavior.SetSize(size, false);
}

void Viewport::SetSize(float width, float height, bool emit)
{
    resizeBehavior.SetSize(width, height, false);
}

void Viewport::SetWidth(float width)
{
    resizeBehavior.SetWidth(width);
}

void Viewport::SetHeight(float height)
{
    resizeBehavior.SetHeight(height);
}

void Viewport::OnUpdate(EventUpdateInfo e)
{
    CalculateAbsolutePosition(moveBehavior.GetPosition());
    CalculateAbsoluteSize(resizeBehavior.GetSize());
}

void Viewport::SetTranslate(const glm::vec2 &offset)
{
    moveBehavior.SetTranslate(offset);
}

void Viewport::SetTranslateX(float x)
{
    moveBehavior.SetTranslateX(x);
}

void Viewport::SetTranslateY(float y)
{
    moveBehavior.SetTranslateY(y);
}

glm::vec2 Viewport::GetTranslate()
{
    return moveBehavior.GetTranslate();
}

float Viewport::GetTranslateX()
{
    return moveBehavior.GetTranslateX();
}

float Viewport::GetTranslateY()
{
    return moveBehavior.GetTranslateY();
}
