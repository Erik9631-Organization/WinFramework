#include "Background.h"
#include "Core/Windows/WindowsCore.h"
#include "RenderingPool.h"

void Background::OnMounted(Presenter &presenter, UiElement& element)
{
    rectangleProxy = std::move(presenter.GetRenderer()->RequestRectangleProxy());
    rectangleProxy->SetSize(element.GetSize());
    rectangleProxy->SetPosition(element.GetAbsolutePosition());
    rectangleProxy->SetColor({255, 255, 255, 255});
    this->presenter = &presenter;
}

void Background::OnMove(EventMoveInfo e)
{
    if(rectangleProxy == nullptr)
        return;
    auto pos = e.GetPosition();
    rectangleProxy->SetPosition(pos);
    presenter->ScheduleRedraw();
}

void Background::OnResize(EventResizeInfo e)
{
    if(rectangleProxy == nullptr)
        return;
   rectangleProxy->SetSize(e.GetSrc()->GetSize());
   presenter->ScheduleRedraw();
}

Background::Background(UiElement &element)
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
