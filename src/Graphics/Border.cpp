//
// Created by erik9 on 2/19/2023.
//

#include "Border.h"
#include "Presenter.h"
#include "UiElement.h"

void Border::OnMounted(Presenter &presenter, UiElement &element)
{
    presenter.GetRenderer()->RequestModel(rectangleProxy);
    this->presenter = &presenter;
    rectangleProxy.SetFill(false);
    rectangleProxy.SetSize(element.GetSize());
    rectangleProxy.SetPosition(element.GetAbsolutePosition() + relativeZIndex);
}

void Border::OnMove(EventMoveInfo e)
{
    auto* movable = dynamic_cast<Movable*>(e.GetSource());
    rectangleProxy.SetPosition(movable->GetAbsolutePosition() + relativeZIndex);
}

void Border::OnResize(EventResizeInfo e)
{
    auto *resizable = dynamic_cast<Resizable *>(e.GetSource());
    if(resizable == nullptr)
        return;
    rectangleProxy.SetSize(resizable->GetSize());
}

Border::Border(UiElement &element) : associatedElement(element)
{
    element.AddOnMoveSubscriber(*this);
    element.AddOnResizeSubscriber(*this);
    element.AddOnMountedSubscriber(*this);
    element.AddViewportSubscriber(*this);
    rectangleProxy.SetColor({0, 0, 0, 255});
}

void Border::SetColor(glm::ivec4 color)
{
    rectangleProxy.SetColor(color);
}

float Border::GetRelativeZIndex()
{
    return relativeZIndex.z;
}

void Border::SetRelativeZIndex(float relativeZIndex)
{
    this->relativeZIndex.z = relativeZIndex;
}

void Border::SetVisible(bool state)
{
    rectangleProxy.SetVisible(state);
}

void Border::ResetViewport()
{
    rectangleProxy.ResetViewport();
}

void Border::SetViewportSize(const glm::vec3 &input)
{
    rectangleProxy.SetViewportSize(input);
}

void Border::SetViewportPosition(const glm::vec3 &input)
{
    rectangleProxy.SetViewportPosition(input);
}

const glm::vec3 & Border::GetViewportSize()
{
    return rectangleProxy.GetViewportSize();
}

const glm::vec3 & Border::GetViewportPosition()
{
    return rectangleProxy.GetViewportSize();
}

void Border::AddViewportSubscriber(ViewportSubscriber &subscriber)
{
    rectangleProxy.AddViewportSubscriber(subscriber);
}

void Border::RemoveViewportSubscriber(ViewportSubscriber &subscriber)
{
    rectangleProxy.RemoveViewportSubscriber(subscriber);
}

void Border::NotifyOnViewportSizeChanged(const ViewportEventInfo &event)
{
    rectangleProxy.NotifyOnViewportSizeChanged(event);
}

void Border::NotifyOnViewportPositionChanged(const ViewportEventInfo &event)
{
    rectangleProxy.NotifyOnViewportPositionChanged(event);
}

bool Border::IsViewportSet() const
{
    return rectangleProxy.IsViewportSet();
}

void Border::NotifyOnViewportReset(const ViewportEventInfo &event)
{
    rectangleProxy.NotifyOnViewportReset(event);
}

void Border::OnViewportSizeChanged(const ViewportEventInfo &event)
{
    rectangleProxy.SetViewportSize(event.GetSize());
}

void Border::OnViewportPositionChanged(const ViewportEventInfo &event)
{
    rectangleProxy.SetViewportPosition(event.GetPosition());
}

void Border::OnViewportReset(const ViewportEventInfo &event)
{
    rectangleProxy.ResetViewport();
}

Border::~Border()
{
    associatedElement.RemoveOnMoveSubscriber(*this);
    associatedElement.RemoveOnResizeSubscriber(*this);
    associatedElement.RemoveOnMountedSubscriber(*this);
    associatedElement.RemoveViewportSubscriber(*this);
}
