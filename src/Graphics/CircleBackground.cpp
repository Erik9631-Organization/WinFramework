#include "CircleBackground.h"
#include "RenderEventInfo.h"
#include "Renderer.h"

void CircleBackground::OnRender(RenderEventInfo e)
{
    Renderer* renderer = e.GetRenderer();
    graphicsUtil.CreateRatio(e.GetParentPosition(), e.GetParentSize());
    renderer->SetColor(color);
    renderer->FillEllipse(graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(), graphicsUtil.GetHeight());
    renderBehavior.OnRender(e);
}
