#include "Button.h"
#include "Core/Windows/WindowsCore.h"
#include "FontAlignment.h"

void Button::SetBorderColor(glm::vec3 color)
{
	border.SetColor(color);
}

void Button::SetBackgroundColor(glm::vec3 color)
{
	//background.SetColor(color);
	buttonBehavior.SetStatelessColor(color);
}

glm::vec3 Button::GetBackgroundColor()
{
    return buttonBehavior.GetStandardColor();
}

glm::vec3 Button::GetBorderColor()
{
	return border.GetColor();
}

void Button::SetBorderThickness(float thickness)
{
	border.SetThickness(thickness);
}

Button::Button(int x, int y, int width, int height) : text("Arial"), buttonBehavior(*this), background(*this)
{
    SetSize(width, height, false);
    SetPosition(x, y, 0, 0, false);
	componentType = "Button";

	border.SetColor({0, 0, 0});
	border.SetThickness(1.0f);

	SetBackgroundColor({30, 30, 30});

	text.SetScalingTypeY(Percentual);
	text.SetScalingTypeY(Percentual);

	text.SetPosition({0.5f, 0.5f, 0, 0});
	text.SetLineAlignment(FontAlingnment::FontAlignmentCenter);
	text.SetAlignment(FontAlingnment::FontAlignmentCenter);

//    renderBehavior.AddRenderCommander(background);
    renderBehavior.AddRenderCommander(border);
    renderBehavior.AddRenderCommander(text);
}

void Button::SetText(std::wstring text)
{
	this->text.SetText(text);
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
