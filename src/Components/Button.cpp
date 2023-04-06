#include "Button.h"
#include "Core/Windows/WindowsCore.h"
#include "FontAlignment.h"

void Button::SetBorderColor(glm::vec3 color)
{
	border.SetColor(glm::vec4{color, 255});
}

void Button::SetBackgroundColor(const glm::vec4 &color)
{
	background.SetColor(color);
	buttonBehavior.SetStatelessColor(color);
}

glm::vec3 Button::GetBackgroundColor()
{
    return buttonBehavior.GetStandardColor();
}

glm::vec3 Button::GetBorderColor()
{
	return glm::vec4{1};
}

Button::Button(int x, int y, int width, int height) : buttonBehavior(*this), background(*this), text(this), border(*this)
{
    SetSize(width, height, false);
    SetPosition(x, y, 0, 0, false);
    componentType = "Button";

    border.SetColor({255, 0, 0, 255});
    //text.SetFontAlignment(FontAlignment::FontAlignmentCenter);
    //text.SetFontAlignment(FontAlignment::FontAlignmentCenter);
}

void Button::SetBorderThickness(float thickness)
{

}

void Button::SetText(std::wstring text)
{
	//this->text.SetText(text);
}

std::wstring Button::GetText()
{
	return text.GetText();
}

Button::~Button()
{

}

void Button::SetOnHoverColor(glm::vec3 color)
{
    buttonBehavior.SetOnHoverColor(color);
}

void Button::SetOnClickColor(glm::vec3 color)
{
    buttonBehavior.SetOnClickColor(color);
}

glm::vec3 Button::GetOnClickColor()
{
    return buttonBehavior.GetOnClickColor();
}

glm::vec3 Button::GetOnHoverColor()
{
    return buttonBehavior.GetOnHoverColor();
}

void Button::SetColor(glm::vec3 color)
{
    
}

void Button::OnMounted(Presenter &presenter, UiElement &element)
{
    UiElement::OnMounted(presenter, element);
    SetBackgroundColor({30, 30, 30, 255});
    //text.SetColor({255, 0, 0, 255});
}
