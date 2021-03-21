#include "SimpleBorder.h"
#include "RenderEventInfo.h"
#include "CoreWindowFrame.h"


SimpleBorder::SimpleBorder() : renderBehavior(*this), reflectionContainer(*this)
{
	//Set up meta data
	reflectionContainer.RegisterMethod("border-color", "SetColor", &SimpleBorder::SetColor);
	reflectionContainer.RegisterMethod("border-style", "SetBorderStyle", &SimpleBorder::SetBorderStyle);
	reflectionContainer.RegisterMethod("border-thickness", "SetThickness", &SimpleBorder::SetThickness);
	
	offset.X = 0.0f;
	offset.Y = 0.0f;

	size.Width = 1.0f;
	size.Height = 1.0f;


	brush = new Gdiplus::SolidBrush(Gdiplus::Color::White);
	pen = new Gdiplus::Pen(brush);
	pen->SetWidth(0.01f);
}


SimpleBorder::~SimpleBorder()
{
	delete pen;
	delete brush;
}

void SimpleBorder::SetColor(Gdiplus::Color color)
{
	this->color = color;
	pen->SetColor(color);
}

Gdiplus::Color SimpleBorder::GetColor()
{
	return color;
}

void SimpleBorder::SetBorderStyle(Gdiplus::DashStyle style)
{
	pen->SetDashStyle(style);
}

void SimpleBorder::SetThickness(float thickness)
{
	pen->SetWidth(thickness / 100);
}

void SimpleBorder::SetScalingType(int type)
{
	scalingType = type;
}

void SimpleBorder::HorizontalCentering(bool state)
{
	horizontalCentering = state;
}

void SimpleBorder::SetVerticalCentering(bool state)
{
	verticalCentering = state;
}

void SimpleBorder::OnRender(RenderEventInfo e)
{
	SizeF calculatedSize(size);
	PointF calculatedPosition(offset);
	if (scalingType == 1)
	{
		calculatedSize.Width = size.Width / e.GetParentSize().Width;
		calculatedSize.Height = size.Height / e.GetParentSize().Height;
	}

	if (verticalCentering)
		calculatedPosition.Y -= calculatedSize.Height / 2;
	if(horizontalCentering)
		calculatedPosition.X -= calculatedSize.Width / 2;

	e.GetGraphics()->DrawRectangle(pen, calculatedPosition.X, calculatedPosition.Y, calculatedSize.Width, calculatedSize.Height);
	renderBehavior.OnRender(e);
}

void SimpleBorder::Repaint()
{

}

void SimpleBorder::AddRenderable(Renderable& renderable)
{
	renderBehavior.AddRenderable(renderable);
}

void SimpleBorder::RemoveRenderable(Renderable& renderable)
{
	renderBehavior.RemoveRenderable(renderable);
}

std::vector<std::reference_wrapper<Renderable>> SimpleBorder::GetRenderables()
{
	return renderBehavior.GetRenderables();
}

bool SimpleBorder::HasMethod(std::string method)
{
	return reflectionContainer.HasMethod(method);
}

ReflectionContainer<SimpleBorder>& SimpleBorder::GetReflectionContainer()
{
	return reflectionContainer;
}

Gdiplus::SizeF& SimpleBorder::GetSize()
{
	return this->size;
}

Gdiplus::PointF& SimpleBorder::GetPercentualPosition()
{
	return this->offset;
}