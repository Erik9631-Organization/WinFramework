#include "Background.h"
#include "Core/Windows/WindowsCore.h"
#include "RenderingPool.h"

void Background::OnMounted(Presenter &presenter, UiElement& element)
{
    rectangleProxy = std::move(presenter.GetRenderer()->RequestRectangleProxy());
    rectangleProxy->SetSize(element.GetSize());
    rectangleProxy->SetPosition(element.GetAbsolutePosition() + relativeZIndex);
    rectangleProxy->SetColor({255, 255, 255, 255});
    this->presenter = &presenter;
}

void Background::OnMove(EventMoveInfo e)
{
    if(rectangleProxy == nullptr)
        return;
    rectangleProxy->SetPosition(e.GetSrc()->GetAbsolutePosition() + relativeZIndex);
    presenter->ScheduleRedraw();
}

void Background::OnResize(EventResizeInfo e)
{
    if(rectangleProxy == nullptr)
        return;
   rectangleProxy->SetSize(e.GetSrc()->GetSize());
   presenter->ScheduleRedraw();
}

Background::Background(UiElement &element) : associatedElement(element)
{
    element.AddOnMoveSubscriber(*this);
    element.AddOnResizeSubscriber(*this);
    element.AddOnMountedSubscriber(*this);
}

void Background::SetColor(glm::ivec4 color)

{
    if(rectangleProxy == nullptr)
        return;
    rectangleProxy->SetColor(color);
}

Background::~Background()
{
    associatedElement.RemoveOnResizeSubscriber(*this);
    associatedElement.RemoveOnMoveSubscriber(*this);
    associatedElement.RemoveOnMountedSubscriber(*this);
}

int Background::GetRelativeZIndex()
{
    return relativeZIndex.z;
}

void Background::SetRelativeZIndex(int relativeZIndex)
{
    this->relativeZIndex.z = relativeZIndex;
}
