#include "Background.h"
#include "EventTypes/RenderEventInfo.h"


Background::Background() : renderBehavior(*this), reflectionContainer(*this), graphicsUtil(position, size)
{
    position = Gdiplus::PointF(0.0f, 0.0f);
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

void Background::SetX (float x)
{
    position.X = x;
}

void Background::SetY(float y)
{
    position.Y = y;
}

float Background::GetWidth()
{
    return size.Width;
}

float Background::GetHeight()
{
    return size.Height;
}

float Background::GetX()
{
    return position.X;
}

float Background::GetY()
{
    return position.Y;
}

void Background::OnRender(RenderEventInfo e)
{
    Gdiplus::SizeF parentSize = Gdiplus::SizeF(e.GetParentSize().Width, e.GetParentSize().Height);
    Gdiplus::PointF parentPos = Gdiplus::PointF(e.GetParentPosition().X, e.GetParentPosition().Y);

    graphicsUtil.UpdateAssociatedParameters(parentPos, parentSize);
    e.GetGraphics()->FillRectangle(brush, graphicsUtil.GetX(), graphicsUtil.GetY(), graphicsUtil.GetWidth(), graphicsUtil.GetHeight());
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

GraphicsScaling Background::GetScalingTypeX() const
{
    return graphicsUtil.GetScalingTypeX();
}

void Background::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    graphicsUtil.SetScalingTypeX(scalingTypeX);
}

GraphicsScaling Background::GetScalingTypeY() const
{
    return graphicsUtil.GetScalingTypeY();
}

void Background::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    graphicsUtil.SetScalingTypeY(scalingTypeY);
}

GraphicsScaling Background::GetScalingTypeWidth() const
{
    return graphicsUtil.GetScalingTypeWidth();
}

void Background::SetScalingTypeWidth(GraphicsScaling scalingTypeWidth)
{
    graphicsUtil.SetScalingTypeWidth(scalingTypeWidth);
}

GraphicsScaling Background::GetScalingTypeHeight() const
{
    return graphicsUtil.GetScalingTypeHeight();
}

void Background::SetScalingTypeHeight(GraphicsScaling scalingTypeHeight)
{
    graphicsUtil.SetScalingTypeHeight(scalingTypeHeight);
}

Gdiplus::SizeF Background::GetSize()
{
    return size;
}

Gdiplus::PointF Background::GetPosition()
{
    return position;
}

void Background::SetPosition(Gdiplus::PointF position)
{
    this->position = position;
}

void Background::SetSize(Gdiplus::SizeF size)
{
    this->size = size;
}
