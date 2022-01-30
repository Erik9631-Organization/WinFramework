#include "Viewport.h"
#include "EventTypes/EventMoveInfo.h"
#include "EventTypes/EventResizeInfo.h"
#include "Components/UiElement.h"
#include "EventTypes/EventUpdateInfo.h"

void Viewport::CalculateAbsolutePosition(Vector2 relative)
{
    absolutePosition.SetX((relative.GetX() + associatedAdjustable.GetAbsoluteX()) * xMultiplier);
    absolutePosition.SetY((relative.GetY() + associatedAdjustable.GetAbsoluteY()) * yMultiplier);
}

void Viewport::CalculateAbsoluteSize(Vector2 size)
{
    absoluteSize.SetX((size.GetX() + associatedAdjustable.GetWidth() + 1) * widthMultiplier);
    absoluteSize.SetY((size.GetY() + associatedAdjustable.GetHeight() + 1) * heightMultiplier);
}

Viewport::Viewport(Adjustable& adjustable) : associatedAdjustable(adjustable), viewportNode((Adjustable&)*this), moveBehavior(viewportNode), resizeBehavior(*this)
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
    return absoluteSize.GetX();
}

int Viewport::GetViewportAbsoluteHeight()
{
    return absoluteSize.GetY();
}

Vector2 Viewport::GetViewportAbsoluteSize()
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

Vector2 Viewport::GetPosition()
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
    return absolutePosition.GetX();
}

float Viewport::GetAbsoluteY()
{
    return absolutePosition.GetY();
}

Vector2 Viewport::GetAbsolutePosition()
{
    return absolutePosition;
}

void Viewport::SetPosition(Vector2 position)
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

Vector2 Viewport::GetSize()
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

void Viewport::SetSize(Vector2 size)
{
    resizeBehavior.SetSize(size);
}

void Viewport::SetSize(float width, float height)
{
    resizeBehavior.SetSize(width, height);
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

void Viewport::SetTranslate(Vector2 offset)
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

Vector2 Viewport::GetTranslate()
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
