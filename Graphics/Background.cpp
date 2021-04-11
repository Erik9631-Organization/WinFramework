#include "Background.h"
#include "RenderEventInfo.h"


Background::Background() : renderBehavior(*this), reflectionContainer(*this)
{
    percentualPos = Gdiplus::PointF(0.0f, 0.0f);
    size = Gdiplus::SizeF(1.0f, 1.0f);

    reflectionContainer.RegisterMethod("background-color", "SetColor", &Background::SetColor);
    reflectionContainer.RegisterMethod("get-background-color", "SetColor", &Background::GetColor);
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

void Background::SetWidth(float width)
{
    size.Width = width;
}

void Background::SetHeight(float height)
{
    size.Height = height;
}

void Background::SetPercentualPosX(float x)
{
    percentualPos.X = x;
}

void Background::SetPercentualPosY(float y)
{
    percentualPos.Y = y;
}

float Background::GetWidth()
{
    return size.Width;
}

float Background::GetHeight()
{
    return size.Height;
}

float Background::GetPercentualPosX()
{
    return percentualPos.X;
}

float Background::GetPercentualPosY()
{
    return percentualPos.Y;
}

void Background::OnRender(RenderEventInfo e)
{
    e.GetGraphics()->FillRectangle(brush, percentualPos.X, percentualPos.Y, size.Width, size.Height);
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
