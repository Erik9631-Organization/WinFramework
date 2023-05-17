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
    auto* movable = dynamic_cast<Movable*>(e.GetSource());
    rectangleProxy.SetPosition(movable->GetAbsolutePosition() + relativeZIndex);
}

void Background::OnResize(EventResizeInfo e)
{
    auto* resizable = dynamic_cast<Resizable*>(e.GetSource());
    if(resizable == nullptr)
        return;
    rectangleProxy.SetSize(resizable->GetSize());
}

Background::Background(UiElement &element) : associatedElement(element)
{
    element.AddOnMoveSubscriber(*this);
    element.AddOnResizeSubscriber(*this);
    element.AddOnMountedSubscriber(*this);
    element.AddViewportSubscriber(*this);

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
    associatedElement.RemoveViewportSubscriber(*this);
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

void Background::AddViewportSubscriber(ViewportSubscriber &subscriber)
{
    rectangleProxy.AddViewportSubscriber(subscriber);
}

void Background::RemoveViewportSubscriber(ViewportSubscriber &subscriber)
{
    rectangleProxy.RemoveViewportSubscriber(subscriber);
}

void Background::NotifyOnViewportSizeChanged(const ViewportEventInfo &event)
{
    rectangleProxy.NotifyOnViewportSizeChanged(event);
}

void Background::NotifyOnViewportPositionChanged(const ViewportEventInfo &event)
{
    rectangleProxy.NotifyOnViewportPositionChanged(event);
}

bool Background::IsViewportSet() const
{
    return rectangleProxy.IsViewportSet();
}

void Background::OnViewportSizeChanged(const ViewportEventInfo &event)
{
    rectangleProxy.SetViewportSize(event.GetSize());
}

void Background::OnViewportPositionChanged(const ViewportEventInfo &event)
{
    rectangleProxy.SetViewportPosition(event.GetPosition());
}

void Background::OnViewportReset(const ViewportEventInfo &event)
{
    rectangleProxy.ResetViewport();
}

void Background::NotifyOnViewportReset(const ViewportEventInfo &event)
{
    rectangleProxy.NotifyOnViewportReset(event);
}
