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
    checkBoxChar.SetPosition(checkboxScaler.GetPosition() + checkboxBorder.GetSize() / 2.0f);
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

void CheckboxGraphics::ResetViewPort()
{
    checkboxBorder.ResetViewPort();
    checkBoxChar.ResetViewPort();
}

void CheckboxGraphics::SetViewPortSize(const glm::vec4 &vec4)
{
    checkboxBorder.SetViewPortSize(vec4);
    checkBoxChar.SetViewPortSize(vec4);
}

void CheckboxGraphics::SetViewPortPosition(const glm::vec4 &vec4)
{
    checkboxBorder.SetViewPortPosition(vec4);
    checkBoxChar.SetViewPortPosition(vec4);
}

glm::vec4 &CheckboxGraphics::GetViewPortSize()
{
    return checkboxBorder.GetViewPortSize();
}

glm::vec4 &CheckboxGraphics::GetViewPortPosition()
{
    return checkboxBorder.GetViewPortPosition();
}
