#include "RadioButtonGraphics.h"
#include "EventTypes/RenderEventInfo.h"
#include <algorithm>
#include <execution>

void RadioButtonGraphics::UpdateFill()
{
	if (fillEnabled)
		fill.SetColor(fillBackground);
	else
		fill.SetColor({0, 0, 0, 0});
}

RadioButtonGraphics::RadioButtonGraphics() : renderBehavior(*this)
{
    AddRenderCommander(fill);
    AddRenderCommander(border);
	fillBackground = {0, 0, 0, 255};
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


void RadioButtonGraphics::SetPosition(Vector2 position)
{
	border.position = position;
	fill.position = position;
}


void RadioButtonGraphics::SetBorderColor(Vector3 borderColor)
{
	border.SetColor(borderColor);
}

void RadioButtonGraphics::SetFillColor(Vector3 color)
{
	fillBackground = {color.GetX(), color.GetY(), color.GetZ(), 0};
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

void RadioButtonGraphics::AddRenderCommander(RenderCommander &renderable)
{
    renderBehavior.AddRenderCommander(renderable);
}

void RadioButtonGraphics::RemoveRenderCommander(RenderCommander& renderable)
{
    renderBehavior.RemoveRenderCommander(renderable);
}

std::vector<std::reference_wrapper<RenderCommander>> RadioButtonGraphics::GetRenderables()
{
	return renderBehavior.GetRenderables();
}

Vector2 RadioButtonGraphics::GetPosition()
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
    return border.position.GetX();
}

float RadioButtonGraphics::GetY()
{
    return border.position.GetY();
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

void RadioButtonGraphics::SetBorderColor(Vector4 borderColor)
{
    border.SetColor(borderColor);
}

void RadioButtonGraphics::SetFillColor(Vector4 color)
{
    fill.SetColor(color);
}

void RadioButtonGraphics::OnSync(const DrawData &data)
{
    renderBehavior.OnSync(data);
}
