#include "Viewport.h"
#include "EventTypes/EventMoveInfo.h"
#include "EventTypes/EventResizeInfo.h"
#include "Components/UiElement.h"
#include "EventTypes/EventUpdateInfo.h"

void Viewport::CalculateAbsolutePosition(Gdiplus::Point relative)
{
    absolutePosition.X = (relative.X + associatedAdjustable.GetAbsoluteX()) * xMultiplier;
    absolutePosition.Y = (relative.Y + associatedAdjustable.GetAbsoluteY()) * yMultiplier;
}

void Viewport::CalculateAbsoluteSize(Gdiplus::Size size)
{
    absoluteSize.Width = (size.Width + associatedAdjustable.GetWidth() + 1) * widthMultiplier;
    absoluteSize.Height = (size.Height + associatedAdjustable.GetHeight() + 1) * heightMultiplier;
}

Viewport::Viewport(Adjustable& adjustable) : associatedAdjustable(adjustable), viewportNode((Adjustable&)*this), moveBehavior(viewportNode), resizeBehavior(*this)
{

    CalculateAbsoluteSize(Gdiplus::Size(0, 0));
    CalculateAbsolutePosition(Gdiplus::Point(0, 0));
    internalOffset = Gdiplus::Point(0, 0);
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
    return absoluteSize.Width;
}

int Viewport::GetViewportAbsoluteHeight()
{
    return absoluteSize.Height;
}

Gdiplus::Size Viewport::GetViewportAbsoluteSize()
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

Gdiplus::Point Viewport::GetPosition()
{
    return moveBehavior.GetPosition();
}

int Viewport::GetX()
{
    return moveBehavior.GetX();
}

int Viewport::GetY()
{
    return moveBehavior.GetY();
}

int Viewport::GetAbsoluteX()
{
    return absolutePosition.X;
}

int Viewport::GetAbsoluteY()
{
    return absolutePosition.Y;
}

Gdiplus::Point Viewport::GetAbsolutePosition()
{
    return absolutePosition;
}

void Viewport::SetPosition(Gdiplus::Point position)
{
    moveBehavior.SetPosition(position);
}

void Viewport::SetPosition(int x, int y)
{
    moveBehavior.SetPosition(x, y);
}

void Viewport::SetX(int x)
{
    moveBehavior.SetX(x);
}

void Viewport::SetY(int y)
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

Gdiplus::Size Viewport::GetSize()
{
    return resizeBehavior.GetSize();
}

int Viewport::GetWidth()
{
    return resizeBehavior.GetWidth();
}

int Viewport::GetHeight()
{
    return resizeBehavior.GetHeight();
}

void Viewport::SetSize(Gdiplus::Size size)
{
    resizeBehavior.SetSize(size);
}

void Viewport::SetSize(int width, int height)
{
    resizeBehavior.SetSize(width, height);
}

void Viewport::SetWidth(int width)
{
    resizeBehavior.SetWidth(width);
}

void Viewport::SetHeight(int height)
{
    resizeBehavior.SetHeight(height);
}

void Viewport::OnUpdate(EventUpdateInfo e)
{
    CalculateAbsolutePosition(moveBehavior.GetPosition());
    CalculateAbsoluteSize(resizeBehavior.GetSize());
}

void Viewport::SetTranslate(Gdiplus::Point offset)
{
    moveBehavior.SetTranslate(offset);
}

void Viewport::SetTranslateX(int x)
{
    moveBehavior.SetTranslateX(x);
}

void Viewport::SetTranslateY(int y)
{
    moveBehavior.SetTranslateY(y);
}

Gdiplus::Point Viewport::GetTranslate()
{
    return moveBehavior.GetTranslate();
}

int Viewport::GetTranslateX()
{
    return moveBehavior.GetTranslateX();
}

int Viewport::GetTranslateY()
{
    return moveBehavior.GetTranslateY();
}
