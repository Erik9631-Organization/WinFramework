#include "CircleBorder.h"
#include "EventTypes/RenderEventInfo.h"

CircleBorder::CircleBorder() : renderBehavior(*this), graphicsUtil(position, size)
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

    Gdiplus::PointF parentPosition = Gdiplus::PointF(e.GetParentPosition().X, e.GetParentPosition().Y);
    Gdiplus::SizeF parentSize = Gdiplus::SizeF(e.GetParentSize().Width, e.GetParentSize().Height);

    graphicsUtil.UpdateAssociatedParameters(parentPosition, parentSize);

    graphics->DrawEllipse(pen, graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(), graphicsUtil.GetHeight());
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

void CircleBorder::SetDiameter(float diameter)
{
    this->size = {diameter, diameter};
    this->diameter = diameter;
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

float CircleBorder::GetDiameter()
{
    return diameter;
}
float CircleBorder::GetThickness()
{
    return thickness;
}

void CircleBorder::SetColor(Gdiplus::Color color)
{
    pen->SetColor(color);
    brush->SetColor(color);
}

GraphicsScaling CircleBorder::GetScalingTypeX() const
{
    return graphicsUtil.GetScalingTypeX();
}

void CircleBorder::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    graphicsUtil.SetScalingTypeX(scalingTypeX);
}

GraphicsScaling CircleBorder::GetScalingTypeY() const
{
    return graphicsUtil.GetScalingTypeY();
}

void CircleBorder::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    return graphicsUtil.SetScalingTypeY(scalingTypeY);
}

GraphicsScaling CircleBorder::GetScalingTypeWidth() const
{
    return graphicsUtil.GetScalingTypeWidth();
}

void CircleBorder::SetScalingTypeWidth(GraphicsScaling scalingTypeWidth)
{
    graphicsUtil.SetScalingTypeWidth(scalingTypeWidth);
}

GraphicsScaling CircleBorder::GetScalingTypeHeight() const
{
    return graphicsUtil.GetScalingTypeHeight();
}

void CircleBorder::SetScalingTypeHeight(GraphicsScaling scalingTypeHeight)
{
    graphicsUtil.SetScalingTypeHeight(scalingTypeHeight);
}

bool CircleBorder::IsDrawFromCenterY() const
{
    return graphicsUtil.IsCalculateFromCenterY();
}

void CircleBorder::SetDrawFromCenterY(bool drawFromCenterY)
{
    graphicsUtil.SetCalculateFromCenterY(drawFromCenterY);
}

bool CircleBorder::IsDrawFromCenterX() const
{
    return graphicsUtil.IsCalculatingFromCenterX();
}

void CircleBorder::SetDrawFromCenterX(bool drawFromCenterX)
{
    graphicsUtil.SetCalculateFromCenterX(drawFromCenterX);
}

Gdiplus::PointF CircleBorder::GetPosition()
{
    return position;
}

void CircleBorder::SetPosition(Gdiplus::PointF point)
{
    this->position = point;
}

void CircleBorder::SetX(float x)
{
    position.X = x;
}

void CircleBorder::SetY(float y)
{
    position.Y = y;
}

float CircleBorder::GetX()
{
    return position.X;
}

float CircleBorder::GetY()
{
    return position.Y;
}
