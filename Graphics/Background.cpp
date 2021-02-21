#include "Background.h"
#include "RenderEventInfo.h"


Background::Background() : renderBehavior(*this), reflectionContainer(*this)
{
    reflectionContainer.RegisterMethod("background-color", "SetColor", &Background::SetColor);
    brush = new Gdiplus::SolidBrush(Gdiplus::Color::White);
}

Background::~Background()
{
    delete brush;
}

void Background::SetColor(Gdiplus::Color color)
{
    currentColor = color;
    brush->SetColor(color);
}

Gdiplus::Color Background::GetColor()
{
    return currentColor;
}

void Background::OnRender(RenderEventInfo e)
{
    e.GetGraphics()->FillRectangle(brush, 0.0f, 0.0f, 1.0f, 1.0f);
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

bool Background::HasMethod(std::string method)
{
    return reflectionContainer.HasMethod(method);
}

ReflectionContainer<Background>& Background::GetReflectionContainer()
{
    return reflectionContainer;
}
