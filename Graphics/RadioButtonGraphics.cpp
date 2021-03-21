#include "RadioButtonGraphics.h"
#include "RenderEventInfo.h"

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

void RadioButtonGraphics::SetRadius(float radius)
{
	border.SetRadius(radius);
	fill.SetRadius(radius - fillPadding);
}

void RadioButtonGraphics::SetPercentualPosition(Gdiplus::PointF percentualPos)
{
	border.percentualPosition = percentualPos;
	fill.percentualPosition = percentualPos;
}

void RadioButtonGraphics::SetOffset(Gdiplus::PointF offset)
{
	border.offset = offset;
	fill.offset = offset;
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

void RadioButtonGraphics::SetDrawFromCenter(bool state)
{
	border.SetDrawFromCenter(state);
	fill.SetDrawFromCenter(state);
}

void RadioButtonGraphics::SetScalingType(int type)
{
	border.SetScalingType(type);
	fill.SetScalingType(type);
}

void RadioButtonGraphics::SetFillPadding(float padding)
{
	this->fillPadding = padding;
	fill.SetRadius(border.GetRadius() - fillPadding);
}

float RadioButtonGraphics::GetFillPadding()
{
	return fillPadding;
}

float RadioButtonGraphics::GetRadius()
{
	return border.GetRadius();
}

Gdiplus::PointF RadioButtonGraphics::GetPercentualPosition()
{
	return border.percentualPosition;
}

Gdiplus::PointF RadioButtonGraphics::GetOffset()
{
	return border.offset;
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
