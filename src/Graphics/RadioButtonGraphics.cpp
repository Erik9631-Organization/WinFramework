#include "RadioButtonGraphics.h"
#include "EventTypes/RenderEventInfo.h"

void RadioButtonGraphics::UpdateFill()
{
	if (fillEnabled)
		fill.SetColor(fillBackground);
	else
		fill.SetColor(Gdiplus::Color::Transparent);
}

RadioButtonGraphics::RadioButtonGraphics() : renderBehavior(*this)
{
	AddRenderable(fill);
	AddRenderable(border);
	fillBackground = Gdiplus::Color::Black;
}

void RadioButtonGraphics::SetFillEnabled(bool state)
{
	fillEnabled = state;
	UpdateFill();

}

void RadioButtonGraphics::SetThickness(float thickness)
{
	border.SetThickness(thickness);
	fill.SetThickness(thickness);
}

void RadioButtonGraphics::SetDiameter(float Diameter)
{
    border.SetDiameter(Diameter);
    fill.SetDiameter(Diameter - fillPadding);
}


void RadioButtonGraphics::SetPosition(Gdiplus::PointF position)
{
	border.position = position;
	fill.position = position;
}


void RadioButtonGraphics::SetBorderColor(Gdiplus::Color borderColor)
{
	border.SetColor(borderColor);
}

void RadioButtonGraphics::SetFillColor(Gdiplus::Color color)
{
	fillBackground = color;
	fill.SetColor(color);
}

void RadioButtonGraphics::SetFillPadding(float padding)
{
	this->fillPadding = padding;
    fill.SetDiameter(border.GetDiameter() - fillPadding);
}

float RadioButtonGraphics::GetFillPadding()
{
	return fillPadding;
}

float RadioButtonGraphics::GetDiameter()
{
	return border.GetDiameter();
}

void RadioButtonGraphics::OnRender(RenderEventInfo e)
{
	renderBehavior.OnRender(e);
}

void RadioButtonGraphics::Repaint()
{

}

void RadioButtonGraphics::AddRenderable(Renderable& renderable)
{
	renderBehavior.AddRenderable(renderable);
}

void RadioButtonGraphics::RemoveRenderable(Renderable& renderable)
{
	renderBehavior.RemoveRenderable(renderable);
}

std::vector<std::reference_wrapper<Renderable>> RadioButtonGraphics::GetRenderables()
{
	return renderBehavior.GetRenderables();
}

Gdiplus::PointF RadioButtonGraphics::GetPosition()
{
    return border.GetPosition();
}

void RadioButtonGraphics::SetX(float x)
{
    border.SetX(x);
    fill.SetX(x);
}

void RadioButtonGraphics::SetY(float y)
{
    border.SetY(y);
    fill.SetY(y);
}

float RadioButtonGraphics::GetX()
{
    return border.position.X;
}

float RadioButtonGraphics::GetY()
{
    return border.position.Y;
}

GraphicsScaling RadioButtonGraphics::GetScalingTypeX() const
{
    return border.GetScalingTypeX();
}

void RadioButtonGraphics::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    border.SetScalingTypeX(scalingTypeX);
    fill.SetScalingTypeX(scalingTypeX);
}

void RadioButtonGraphics::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    border.SetScalingTypeY(scalingTypeY);
    fill.SetScalingTypeY(scalingTypeY);
}

GraphicsScaling RadioButtonGraphics::GetScalingTypeWidth() const
{
    return border.GetScalingTypeWidth();
}

void RadioButtonGraphics::SetScalingTypeWidth(GraphicsScaling scalingTypeWidth)
{
    border.SetScalingTypeWidth(scalingTypeWidth);
    fill.SetScalingTypeWidth(scalingTypeWidth);
}

GraphicsScaling RadioButtonGraphics::GetScalingTypeHeight() const
{
    return border.GetScalingTypeHeight();
}

void RadioButtonGraphics::SetScalingTypeHeight(GraphicsScaling scalingTypeHeight)
{
    border.SetScalingTypeHeight(scalingTypeHeight);
    fill.SetScalingTypeHeight(scalingTypeHeight);
}

bool RadioButtonGraphics::IsDrawFromCenterY() const
{
    return border.IsDrawFromCenterY();
}

void RadioButtonGraphics::SetDrawFromCenterY(bool drawFromCenterY)
{
    border.SetDrawFromCenterY(drawFromCenterY);
    fill.SetDrawFromCenterY(drawFromCenterY);
}

bool RadioButtonGraphics::IsDrawFromCenterX() const
{
    return border.IsDrawFromCenterX();
}

void RadioButtonGraphics::SetDrawFromCenterX(bool drawFromCenterX)
{
    border.SetDrawFromCenterX(drawFromCenterX);
    fill.SetDrawFromCenterX(drawFromCenterX);
}
