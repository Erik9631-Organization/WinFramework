#include "CircleBackground.h"
#include "RenderEventInfo.h"

void CircleBackground::OnRender(RenderEventInfo e)
{
    Gdiplus::Graphics* graphics = e.GetGraphics();
    Gdiplus::PointF position;

    position.X = percentualPosition.X + (offset.X / (float)e.GetParentSize().Width);
    position.Y = percentualPosition.Y + (offset.Y / (float)e.GetParentSize().Height);

    float diameterX = diameter;
    float diameterY = diameter;
    if (scalingType == 1)
    {
        diameterX = diameter / (float)e.GetParentSize().Width;
        diameterY = diameter / (float)e.GetParentSize().Height;
    }

    if (drawFromCenter == true)
    {
        position.X -= diameterX / 2.0f;
        position.Y -= diameterY / 2.0f;
    }
    graphics->FillEllipse(brush, position.X, position.Y, diameterX, diameterY);
    renderBehavior.OnRender(e);
}
