#include "CircleBackground.h"
#include "RenderEventInfo.h"
#include "Renderer.h"
#include "RenderingPool.h"

void CircleBackground::OnRenderSync(RenderEventInfo e)
{
    Renderer& renderer = e.GetRenderer()->Acquire(*this);
    graphicsUtil.CreateRatio(drawData.GetPosition(), drawData.GetSize());
    renderer.SetColor(color);
    renderer.FillEllipse(graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(), graphicsUtil.GetHeight());
    renderBehavior.OnRenderSync(e);
}
