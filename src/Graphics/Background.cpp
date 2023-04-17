#include "Background.h"
#include "Core/Windows/WindowsCore.h"
#include "RenderingPool.h"

void Background::OnMounted(Presenter &presenter, UiElement& element)
{
    //    presenter.GetRenderer()->RequestModel(Commands::RequestEllipse, rectangleProxy);
    presenter.GetRenderer()->RequestRectangleModel(rectangleProxy);
    this->presenter = &presenter;
    rectangleProxy.SetSize(element.GetSize());
    rectangleProxy.SetPosition(element.GetAbsolutePosition() + relativeZIndex);
}

void Background::OnMove(EventMoveInfo e)
{
    rectangleProxy.SetPosition(e.GetSrc()->GetAbsolutePosition() + relativeZIndex);
}

void Background::OnResize(EventResizeInfo e)
{
   rectangleProxy.SetSize(e.GetSrc()->GetSize());
}

Background::Background(UiElement &element) : associatedElement(element)
{
    element.AddOnMoveSubscriber(*this);
    element.AddOnResizeSubscriber(*this);
    element.AddOnMountedSubscriber(*this);

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
}

float Background::GetRelativeZIndex()
{
    return relativeZIndex.z;
}

void Background::SetRelativeZIndex(float relativeZIndex)
{
    this->relativeZIndex.z = relativeZIndex;
}
