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
        checkboxScaler(element.GetAbsolutePosition(), element.GetSize())
{
    element.AddOnMoveSubscriber(*this);
    element.AddOnResizeSubscriber(*this);
    element.AddOnMountedSubscriber(*this);
    checkboxBorder.SetColor({0, 0, 0, 255});
    checkboxBorder.SetFill(false);
    checkBoxChar.SetColor({0, 0, 0, 255});
    checkBoxChar.SetText(L"✓");
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
