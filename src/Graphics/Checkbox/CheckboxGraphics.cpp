//
// Created by erik9 on 4/22/2023.
//

#include "CheckboxGraphics.h"
#include "UiElement.h"
#include <iostream>

float CheckboxGraphics::GetRelativeZIndex()
{
    return 0;
}

void CheckboxGraphics::SetRelativeZIndex(float relativeZIndex)
{

}

void CheckboxGraphics::SetVisible(bool state)
{
    checkboxBorder.SetVisible(state);
    checkBoxChar.SetVisible(state);
}

void CheckboxGraphics::OnMounted(Presenter &presenter, UiElement &element)
{
    presenter.GetRenderer()->RequestModel(checkboxBorder);
    presenter.GetRenderer()->RequestModel(checkBoxChar);
    UpdateGraphics();
}

void CheckboxGraphics::OnMove(EventMoveInfo e)
{
    UpdateGraphics();
}

void CheckboxGraphics::OnResize(EventResizeInfo e)
{
    UpdateGraphics();
}

//TODO Fix inconsitencies in parameter refernce vs pointer
CheckboxGraphics::CheckboxGraphics(UiElement &element) :
        checkboxScaler(element.GetAbsolutePosition(), element.GetSize()),
        associatedElement(element)
{
    element.AddOnMoveSubscriber(*this);
    element.AddOnResizeSubscriber(*this);
    element.AddOnMountedSubscriber(*this);
    element.AddViewport2Subscriber(*this);
    checkboxBorder.SetColor({0, 0, 0, 255});
    checkboxBorder.SetFill(false);
    checkBoxChar.SetColor({0, 0, 0, 255});
    checkBoxChar.SetText(L"✔");
    checkBoxChar.SetVisible(false);
    checkBoxChar.SetFontSize(14.0f);
    checkboxBorder.SetSize(20, 20);
    checkboxScaler.SetUnitTypePosX(GraphicsScaling::Percentual);
    checkboxScaler.SetUnitTypePosY(GraphicsScaling::Percentual);

    checkBoxChar.SetFontAlignment(FontAlignment::FontAlignmentCenter);
    checkBoxChar.SetFontLineAlignment(FontAlignment::FontAlignmentCenter);
    UpdateGraphics();

}

void CheckboxGraphics::UpdateGraphics()
{
    checkboxScaler.Scale(checkboxPosition);
    checkboxBorder.SetPosition(checkboxScaler.GetPosition());
    checkBoxChar.SetPosition(checkboxScaler.GetPosition() + glm::vec3{checkboxBorder.GetSize()} / 2.0f);
}

void CheckboxGraphics::SetCheck(bool state)
{
    checked = state;
    checkBoxChar.SetVisible(state);
}

bool CheckboxGraphics::IsChecked()
{
    return checked;
}

void CheckboxGraphics::ResetViewport()
{
    checkboxBorder.ResetViewport();
    checkBoxChar.ResetViewport();
}

void CheckboxGraphics::SetViewportSize(const glm::vec4 &vec4)
{
    checkboxBorder.SetViewportSize(vec4);
    checkBoxChar.SetViewportSize(vec4);
}

void CheckboxGraphics::SetViewportPosition(const glm::vec3 &input)
{
    checkboxBorder.SetViewportPosition(input);
    checkBoxChar.SetViewportPosition(input);
}

const glm::vec4 & CheckboxGraphics::GetViewportSize()
{
    return checkboxBorder.GetViewportSize();
}

const glm::vec3 & CheckboxGraphics::GetViewportPosition()
{
    return checkboxBorder.GetViewportPosition();
}

void CheckboxGraphics::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    checkboxBorder.AddViewport2Subscriber(subscriber);
    checkBoxChar.AddViewport2Subscriber(subscriber);
}

void CheckboxGraphics::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    checkboxBorder.RemoveViewport2Subscriber(subscriber);
    checkBoxChar.RemoveViewport2Subscriber(subscriber);
}

void CheckboxGraphics::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    checkboxBorder.NotifyOnViewportSizeChanged(event);
    checkBoxChar.NotifyOnViewportSizeChanged(event);
}

void CheckboxGraphics::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    checkboxBorder.NotifyOnViewportPositionChanged(event);
    checkBoxChar.NotifyOnViewportPositionChanged(event);
}

bool CheckboxGraphics::IsViewportSet() const
{
    return checkboxBorder.IsViewportSet() || checkBoxChar.IsViewportSet();
}

void CheckboxGraphics::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    checkboxBorder.NotifyOnViewportReset(event);
    checkBoxChar.NotifyOnViewportReset(event);
}

void CheckboxGraphics::OnViewportSizeChanged(const Viewport2EventInfo &event)
{
    checkBoxChar.SetViewportSize(event.GetSize());
}

void CheckboxGraphics::OnViewportPositionChanged(const Viewport2EventInfo &event)
{
    checkBoxChar.SetViewportPosition(event.GetPosition());
}

void CheckboxGraphics::OnViewportReset(const Viewport2EventInfo &event)
{
    checkBoxChar.ResetViewport();
}

CheckboxGraphics::~CheckboxGraphics()
{
    associatedElement.RemoveOnMoveSubscriber(*this);
    associatedElement.RemoveOnResizeSubscriber(*this);
    associatedElement.RemoveOnMountedSubscriber(*this);
    associatedElement.RemoveViewport2Subscriber(*this);
}
