//
// Created by erik9 on 2/19/2023.
//

#include "Border.h"
#include "Presenter.h"
#include "UiElement.h"

void Border::OnMounted(Presenter &presenter, UiElement &element)
{
    rectangleProxy = std::move(presenter.GetRenderer()->RequestRectangleProxy());
    rectangleProxy->SetFill(false);
    rectangleProxy->SetSize(element.GetSize());
    rectangleProxy->SetPosition(element.GetAbsolutePosition());
    rectangleProxy->SetColor({255, 255, 255, 255});
    this->presenter = &presenter;
}

void Border::OnMove(EventMoveInfo e)
{
    if(rectangleProxy == nullptr)
        return;
    rectangleProxy->SetPosition(e.GetSrc()->GetAbsolutePosition());
    presenter->ScheduleRedraw();
}

void Border::OnResize(EventResizeInfo e)
{
    if(rectangleProxy == nullptr)
        return;
    rectangleProxy->SetSize(e.GetSrc()->GetSize());
    presenter->ScheduleRedraw();
}

Border::Border(UiElement &element) : associatedElement(element)
{
    element.AddOnMoveSubscriber(*this);
    element.AddOnResizeSubscriber(*this);
    element.AddOnMountedSubscriber(*this);
}

void Border::SetColor(glm::ivec4 color)
{
    if(rectangleProxy == nullptr)
        return;
    rectangleProxy->SetColor(color);
}

int Border::GetRelativeZIndex()
{
    return relativeZIndex;
}

void Border::SetRelativeZIndex(int relativeZIndex)
{
    this->relativeZIndex = relativeZIndex;
}
