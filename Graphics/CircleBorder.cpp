#include "CircleBorder.h"
#include "RenderEventInfo.h"

CircleBorder::CircleBorder() : renderBehavior(*this)
{
    brush = new Gdiplus::SolidBrush(Gdiplus::Color::Black);
    pen = new Gdiplus::Pen(brush);
    thickness = 1.0f / 100.0f;
    pen->SetWidth(thickness);
    pen->SetColor(Gdiplus::Color::Black);
}

CircleBorder::~CircleBorder()
{
    delete pen;
    delete brush;
}

void CircleBorder::OnRender(RenderEventInfo e)
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
    graphics->DrawEllipse(pen, position.X, position.Y, diameterX, diameterY);
    renderBehavior.OnRender(e);
}

void CircleBorder::Repaint()
{
}

void CircleBorder::AddRenderable(Renderable& renderable)
{
    renderBehavior.AddRenderable(renderable);
}

void CircleBorder::RemoveRenderable(Renderable& renderable)
{
    renderBehavior.RemoveRenderable(renderable);
}

void CircleBorder::SetRadius(float radius)
{
    this->diameter = radius;
}

std::vector<std::reference_wrapper<Renderable>> CircleBorder::GetRenderables()
{
    return renderBehavior.GetRenderables();
}

void CircleBorder::SetThickness(float thickness)
{
    this->thickness = thickness / 100;
    pen->SetWidth(this->thickness);
}

float CircleBorder::GetRadius()
{
    return diameter;
}
float CircleBorder::GetThickness()
{
    return thickness;
}

void CircleBorder::SetDrawFromCenter(bool state)
{
    this->drawFromCenter = state;
}

void CircleBorder::SetScalingType(int scalingType)
{
    this->scalingType = scalingType;
}

void CircleBorder::SetColor(Gdiplus::Color color)
{
    pen->SetColor(color);
    brush->SetColor(color);
}
