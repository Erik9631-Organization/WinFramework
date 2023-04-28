#include "Button.h"
#include "Core/Windows/WindowsCore.h"
#include "FontAlignment.h"

void Button::SetBorderColor(const glm::ivec4 &color)
{
	border.SetColor(color);
}

void Button::SetBackgroundColor(const glm::ivec4 &color)
{
	background.SetColor(color);
}

const glm::ivec4 & Button::GetBackgroundColor()
{
    return buttonBehavior.GetStandardColor();
}

const glm::ivec4 & Button::GetBorderColor()
{
	return glm::vec4{0};
}

Button::Button(float x, float y, float width, float height, const std::string& name = "") : UiElement(x, y, width, height, name),
    buttonBehavior(*this),
    background(*this),
    text(*this),
    border(*this)
{
    componentType = "Button";
    border.SetColor({0, 0, 0, 255});
    text.SetFontAlignment(FontAlignment::FontAlignmentCenter);
    text.SetFontLineAlignment(FontAlignment::FontAlignmentCenter);
    text.SetColor({255, 0, 0, 255});
}

void Button::SetBorderThickness(float thickness)
{

}

void Button::SetText(std::wstring text)
{
	this->text.SetText(text);
}

const std::wstring & Button::GetText()
{
	return text.GetText();
}

void Button::SetOnHoverColor(const glm::ivec4 &color)
{
    buttonBehavior.SetOnHoverBackgroundColor(color);
}

void Button::SetOnClickColor(const glm::vec4 &color)
{
    buttonBehavior.SetOnClickBackgroundColor(color);
}

const glm::ivec4 & Button::GetOnClickColor()
{
    return buttonBehavior.GetOnClickColor();
}

const glm::ivec4 & Button::GetOnHoverColor()
{
    return buttonBehavior.GetOnHoverColor();
}

void Button::SetStatelessBackgroundColor(const glm::ivec4 &color)
{
    buttonBehavior.SetBackgroundColor(color);
}
