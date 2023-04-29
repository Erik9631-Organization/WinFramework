#include "Background.h"
#include "Core/Windows/WindowsCore.h"
#include "RenderingPool.h"

void Background::OnMounted(Presenter &presenter, UiElement& element)
{
    presenter.GetRenderer()->RequestModel(rectangleProxy);
    this->presenter = &presenter;
    rectangleProxy.SetSize(element.GetSize());
    rectangleProxy.SetPosition(element.GetAbsolutePosition() + relativeZIndex);
}

void Background::OnMove(EventMoveInfo e)
{
    rectangleProxy.SetPosition(e.GetSrc()->GetAbsolutePosition() + relativeZIndex);
}

void Background::OnResize(EventResizeInfo e)
{
   rectangleProxy.SetSize(e.GetSrc()->GetSize());
}

Background::Background(UiElement &element) : associatedElement(element)
{
    element.AddOnMoveSubscriber(*this);
    element.AddOnResizeSubscriber(*this);
    element.AddOnMountedSubscriber(*this);
    element.AddViewport2Subscriber(*this);

}

void Background::SetColor(glm::ivec4 color)
{
    rectangleProxy.SetColor(color);
}

Background::~Background()
{
    associatedElement.RemoveOnResizeSubscriber(*this);
    associatedElement.RemoveOnMoveSubscriber(*this);
    associatedElement.RemoveOnMountedSubscriber(*this);
    associatedElement.RemoveViewport2Subscriber(*this);
}

float Background::GetRelativeZIndex()
{
    return relativeZIndex.z;
}

void Background::SetRelativeZIndex(float relativeZIndex)
{
    this->relativeZIndex.z = relativeZIndex;
}

void Background::SetVisible(bool state)
{
    rectangleProxy.SetVisible(false);
}

const glm::ivec4 &Background::GetColor()
{
    return rectangleProxy.GetColor();
}

void Background::ResetViewport()
{
    rectangleProxy.ResetViewport();
}

void Background::SetViewportSize(const glm::vec3 &input)
{
    rectangleProxy.SetViewportSize(input);
}

void Background::SetViewportPosition(const glm::vec3 &input)
{
    rectangleProxy.SetViewportPosition(input);
}

const glm::vec3 & Background::GetViewportSize()
{
    return rectangleProxy.GetViewportSize();
}

const glm::vec3 & Background::GetViewportPosition()
{
    return rectangleProxy.GetViewportPosition();
}

void Background::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    rectangleProxy.AddViewport2Subscriber(subscriber);
}

void Background::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    rectangleProxy.RemoveViewport2Subscriber(subscriber);
}

void Background::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    rectangleProxy.NotifyOnViewportSizeChanged(event);
}

void Background::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    rectangleProxy.NotifyOnViewportPositionChanged(event);
}

bool Background::IsViewportSet() const
{
    return rectangleProxy.IsViewportSet();
}

void Background::OnViewportSizeChanged(const Viewport2EventInfo &event)
{
    rectangleProxy.SetViewportSize(event.GetSize());
}

void Background::OnViewportPositionChanged(const Viewport2EventInfo &event)
{
    rectangleProxy.SetViewportPosition(event.GetPosition());
}

void Background::OnViewportReset(const Viewport2EventInfo &event)
{
    rectangleProxy.ResetViewport();
}

void Background::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    rectangleProxy.NotifyOnViewportReset(event);
}
