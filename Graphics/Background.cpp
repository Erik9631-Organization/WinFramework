#include "Background.h"
#include "RenderEventInfo.h"


Background::Background() : renderBehavior(*this)
{
    brush = new Gdiplus::SolidBrush(Gdiplus::Color::White);
}

Background::~Background()
{
    delete brush;
}

void Background::SetColor(Gdiplus::Color color)
{
    brush->SetColor(color);
}

void Background::OnRender(RenderEventInfo e)
{
    e.GetGraphics()->FillRectangle(brush, 0, 0, 1, 1);
}

void Background::Repaint()
{
}

void Background::AddRenderable(Renderable& renderable)
{
    renderBehavior.AddRenderable(renderable);
}

void Background::RemoveRenderable(Renderable& renderable)
{
    renderBehavior.RemoveRenderable(renderable);
}

std::vector<std::reference_wrapper<Renderable>> Background::GetRenderables()
{
    return std::vector<std::reference_wrapper<Renderable>>();
}
