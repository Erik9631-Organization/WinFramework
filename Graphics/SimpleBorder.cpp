#include "SimpleBorder.h"
#include "RenderEventInfo.h"
#include "CoreWindowFrame.h"


SimpleBorder::SimpleBorder() : renderBehavior(*this), reflectionContainer(*this)
{
	//Set up meta data
	reflectionContainer.RegisterMethod("border-color", "SetColor", &SimpleBorder::SetColor);
	reflectionContainer.RegisterMethod("border-style", "SetBorderStyle", &SimpleBorder::SetBorderStyle);
	reflectionContainer.RegisterMethod("border-thickness", "SetThickness", &SimpleBorder::SetThickness);


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

void SimpleBorder::OnRender(RenderEventInfo e)
{
	e.GetGraphics()->DrawRectangle(pen, 0.0f, 0.0f, 1.0f, 1.0f);
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

