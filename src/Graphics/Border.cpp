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
    rectangleProxy.SetPosition(e.GetSrc()->GetAbsolutePosition() + relativeZIndex);
}

void Border::OnResize(EventResizeInfo e)
{
    rectangleProxy.SetSize(e.GetSrc()->GetSize());
}

Border::Border(UiElement &element) : associatedElement(element)
{
    element.AddOnMoveSubscriber(*this);
    element.AddOnResizeSubscriber(*this);
    element.AddOnMountedSubscriber(*this);
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

void Border::ResetViewPort()
{
    rectangleProxy.ResetViewPort();
}

void Border::SetViewPortSize(const glm::vec4 &vec4)
{
    rectangleProxy.SetViewPortSize(vec4);
}

void Border::SetViewPortPosition(const glm::vec4 &vec4)
{
    rectangleProxy.SetViewPortPosition(vec4);
}

glm::vec4 &Border::GetViewPortSize()
{
    return rectangleProxy.GetViewPortSize();
}

glm::vec4 &Border::GetViewPortPosition()
{
    return rectangleProxy.GetViewPortSize();
}
