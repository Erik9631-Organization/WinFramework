#include "CircleBackground.h"
#include "RenderEventInfo.h"
#include "RenderingApi.h"
#include "RenderingPool.h"

void CircleBackground::OnRenderSync(RenderEventInfo e)
{
    RenderingApi& renderer = e.GetRenderer()->Acquire(*this);
    graphicsUtil.CreateRatio(drawData.GetPosition(), drawData.GetSize());
    renderer.SetColor(color);
    renderer.DrawFillEllipse(graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(),
                             graphicsUtil.GetHeight());
    renderBehavior.OnRenderSync(e);
}
