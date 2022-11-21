#include "Text.h"
#include "EventTypes/RenderEventInfo.h"
#include "MetaObjects/ClassMethod.h"
#include "FontFormat.h"
#include "RenderingPool.h"

void Text::SetLineAlignment(int alignment)
{
    this->lineAlignment = alignment;
}

void Text::SetAlignment(int alignment)
{
    this->alignment = alignment;
}

int Text::GetLineAlignment()
{
    return lineAlignment;
}

int Text::GetAlignment()
{
    return alignment;
}


Text::Text(std::string fontFamily) : renderBehavior(*this), reflectionContainer(*this), graphicsUtil(position)
{
    reflectionContainer.RegisterMethod("text-color", "SetColor", &Text::SetColor);
    reflectionContainer.RegisterMethod("font-size", "SetFontSize", &Text::SetFontSize);

    std::wstring family = std::wstring(fontFamily.begin(), fontFamily.end());
    this->fontFamily = family;
    this->color = {255, 255, 255, 255};
    position = {0, 0};
}

void Text::SetText(std::wstring text)
{
    this->text = text;
}

std::wstring Text::GetText()
{
    return this->text;
}

void Text::SetPosition(glm::vec2 position)
{
    this->position = position;
}

glm::vec2 Text::GetPosition()
{
    return position;
}

void Text::SetColor(Vector3 color)
{
    this->color = {color.GetX(), color.GetY(), color.GetZ(), 255};
}

void Text::SetFontSize(float fontSize)
{
    this->fontSize = fontSize;
}

void Text::OnRenderSync(RenderEventInfo e)
{
    Renderer& renderer = e.GetRenderer()->Acquire(*this);
    graphicsUtil.CreateRatio(drawData.GetPosition(), drawData.GetSize());
    std::unique_ptr<FontFormat> format = renderer.CreateFontFormat();
    format->SetAlignment(alignment);
    format->SetLineAlignment(lineAlignment);
    renderer.SetColor(color);
    renderer.SetFontFamily(fontFamily);
    renderer.DrawString(text, graphicsUtil.GetPosition(), *format, text.size());
}

void Text::Repaint()
{

}

void Text::AddRenderCommander(RenderCommander &renderable)
{
    renderBehavior.AddRenderCommander(renderable);
}

void Text::RemoveRenderCommander(RenderCommander& renderable)
{
    renderBehavior.RemoveRenderCommander(renderable);
}

std::vector<std::reference_wrapper<RenderCommander>> Text::GetRenderables()
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
    position.x = x;
}

void Text::SetY(float y)
{
    position.y = y;
}

float Text::GetX()
{
    return position.x;
}

float Text::GetY()
{
    return position.y;
}

void Text::OnSync(const DrawData &data)
{
    drawData = DrawData2D(static_cast<const DrawData2D&>(data));
}
