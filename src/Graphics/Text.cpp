#include "Text.h"
#include "EventTypes/RenderEventInfo.h"
#include "MetaObjects/ClassMethod.h"

void Text::SetLineAlignment(Gdiplus::StringAlignment alignment)
{
    this->lineAlignment = alignment;
}

void Text::SetAlignment(Gdiplus::StringAlignment alignment)
{
    this->alignment = alignment;
}

Gdiplus::StringAlignment Text::GetLineAlignment()
{
    return lineAlignment;
}

Gdiplus::StringAlignment Text::GetAlignment()
{
    return alignment;
}


Text::Text(std::string fontFamily) : renderBehavior(*this), reflectionContainer(*this), graphicsUtil(position)
{
    reflectionContainer.RegisterMethod("text-color", "SetColor", &Text::SetColor);
    reflectionContainer.RegisterMethod("font-size", "SetFontSize", &Text::SetFontSize);

    std::wstring family = std::wstring(fontFamily.begin(), fontFamily.end());
    this->fontFamily = new Gdiplus::FontFamily(family.c_str());
    font = new Gdiplus::Font(this->fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    brush = new Gdiplus::SolidBrush(Gdiplus::Color::White);
    position = Gdiplus::PointF(0, 0);
}

void Text::SetText(std::wstring text)
{
    this->text = text;
}

std::wstring Text::GetText()
{
    return this->text;
}

void Text::SetPosition(Gdiplus::PointF position)
{
    this->position = position;
}

Gdiplus::PointF Text::GetPosition()
{
    return position;
}

void Text::SetColor(Gdiplus::Color color)
{
    brush->SetColor(color);
}

void Text::SetFontSize(double fontSize)
{
    this->fontSize = fontSize;
    delete font;
    font = new Gdiplus::Font(this->fontFamily, fontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
}

void Text::OnRender(RenderEventInfo e)
{

    Gdiplus::PointF parentPosition = Gdiplus::PointF(e.GetParentPosition().X, e.GetParentPosition().Y);
    Gdiplus::SizeF parentSize = Gdiplus::SizeF(e.GetParentSize().Width, e.GetParentSize().Height);

    graphicsUtil.UpdateAssociatedParameters(parentPosition, parentSize);

    Gdiplus::StringFormat format;
    format.SetAlignment(alignment);
    format.SetLineAlignment(lineAlignment);
    e.GetGraphics()->DrawString(text.c_str(), -1, font, graphicsUtil.GetPosition(), &format, brush);

}

void Text::Repaint()
{

}

void Text::AddRenderable(Renderable& renderable)
{
    renderBehavior.AddRenderable(renderable);
}

void Text::RemoveRenderable(Renderable& renderable)
{
    renderBehavior.RemoveRenderable(renderable);
}

std::vector<std::reference_wrapper<Renderable>> Text::GetRenderables()
{
    return renderBehavior.GetRenderables();
}

bool Text::HasMethod(std::string method)
{
    return reflectionContainer.HasMethod(method);
}

ReflectionContainer<Text>& Text::GetReflectionContainer()
{
    return reflectionContainer;
}

GraphicsScaling Text::GetScalingTypeX() const
{
    return graphicsUtil.GetScalingTypeX();
}

void Text::SetScalingTypeX(GraphicsScaling scalingTypeX)
{
    return graphicsUtil.SetScalingTypeX(scalingTypeX);
}

GraphicsScaling Text::GetScalingTypeY() const
{
    return graphicsUtil.GetScalingTypeY();
}

void Text::SetScalingTypeY(GraphicsScaling scalingTypeY)
{
    graphicsUtil.SetScalingTypeY(scalingTypeY);
}

void Text::SetX(float x)
{
    position.X = x;
}

void Text::SetY(float y)
{
    position.Y = y;
}

float Text::GetX()
{
    return position.X;
}

float Text::GetY()
{
    return position.Y;
}
