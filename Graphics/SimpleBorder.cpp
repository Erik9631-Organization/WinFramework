#include "SimpleBorder.h"
#include "RenderEventInfo.h"


SimpleBorder::SimpleBorder() : renderBehavior(*this)
{
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
	pen->SetColor(color);
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
