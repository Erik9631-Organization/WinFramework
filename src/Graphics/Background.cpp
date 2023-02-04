#include "Background.h"
#include "Core/Windows/WindowsCore.h"
#include "RenderingPool.h"

void Background::OnMounted(Presenter &presenter, UiElement& element)
{
    presenter.GetRenderer()->RequestRectangleProxy([&](std::unique_ptr<RectangleProxy> proxy){
        rectangleProxy = std::move(proxy);
        rectangleProxy->SetPosition(element.GetAbsolutePosition());
        rectangleProxy->SetSize(element.GetSize());
        rectangleProxy->SetColor(glm::ivec4(255, 255, 255, 255));
        rectangleProxy->BindViewPortToResizable(element);
    });
    this->presenter = &presenter;
}

void Background::OnMove(EventMoveInfo e)
{
    rectangleProxy->SetPosition(e.GetSrc()->GetAbsolutePosition());
    presenter->ScheduleRedraw();
}

void Background::OnResize(EventResizeInfo e)
{
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
    rectangleProxy->SetColor(color);
}
