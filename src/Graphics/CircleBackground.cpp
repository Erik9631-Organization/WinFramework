#include "CircleBackground.h"
#include "RenderEventInfo.h"
#include "ShapeRenderer.h"
#include "RenderingPool.h"

void CircleBackground::OnRenderSync(RenderEventInfo e)
{
    ShapeRenderer& renderer = e.GetRenderer()->Acquire(*this);
    graphicsUtil.Scale(drawData.GetSize());
    renderer.SetColor(color);
    renderer.DrawFillEllipse(graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(),
                             graphicsUtil.GetHeight());
    renderBehavior.OnRenderSync(e);
}
