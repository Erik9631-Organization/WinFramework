#include "CircleBackground.h"
#include "RenderEventInfo.h"

void CircleBackground::OnRender(RenderEventInfo e)
{
    Gdiplus::Graphics* graphics = e.GetGraphics();

    Gdiplus::PointF parentPosition = Gdiplus::PointF(e.GetParentPosition().X, e.GetParentPosition().Y);
    Gdiplus::SizeF parentSize = Gdiplus::SizeF(e.GetParentSize().Width, e.GetParentSize().Height);
    graphicsUtil.UpdateAssociatedParameters(parentPosition, parentSize);

    graphics->FillEllipse(brush, graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(), graphicsUtil.GetHeight());
    renderBehavior.OnRender(e);
}
