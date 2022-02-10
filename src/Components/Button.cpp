#include "Button.h"
#include "CoreWindow.h"
#include "EventTypes/RenderEventInfo.h"
#include "FontAlignment.h"
void Button::SetBorderColor(Vector3 color)
{
	border.SetColor(color);
	//Repaint();
}

void Button::SetBackgroundColor(Vector3 color)
{
	background.SetColor(color);
	buttonBehavior.SetStatelessColor(color);
	//Repaint();
}


Vector3 Button::GetBackgroundColor()
{
    return buttonBehavior.GetStandardColor();
}

Vector3 Button::GetBorderColor()
{
	return border.GetColor();
}

void Button::SetBorderThickness(float thickness)
{
	border.SetThickness(thickness);
	//Repaint();
}


Button::Button(int x, int y, int width, int height) : text("Arial"), buttonBehavior(*this)
{
	SetSize(width, height);
	SetPosition(x, y);
	componentType = "Button";

	border.SetColor({0, 0, 0});
	border.SetThickness(1.0f);

	SetBackgroundColor({30, 30, 30});

	text.SetScalingTypeY(Percentual);
	text.SetScalingTypeY(Percentual);

	text.SetPosition({0.5f, 0.5f});
	text.SetLineAlignment(FontAlingnment::FontAlignmentCenter);
	text.SetAlignment(FontAlingnment::FontAlignmentCenter);

	renderBehavior.AddRenderable(background);
	renderBehavior.AddRenderable(border);
	renderBehavior.AddRenderable(text);
}

void Button::SetText(std::wstring text)
{
	this->text.SetText(text);
	//Repaint();
}

std::wstring Button::GetText()
{
	return text.GetText();
}


Button::~Button()
{

}

void Button::SetOnHoverColor(Vector3 color)
{
    buttonBehavior.SetOnHoverColor(color);
}

void Button::SetOnClickColor(Vector3 color)
{
    buttonBehavior.SetOnClickColor(color);
}


void Button::SetColor(Vector3 color)
{
    background.SetColor(color);
    //Repaint();
}

Vector3 Button::GetOnClickColor()
{
    return buttonBehavior.GetOnClickColor();
}

Vector3 Button::GetOnHoverColor()
{
    return buttonBehavior.GetOnHoverColor();
}

Vector3 Button::GetColor()
{
    return background.GetColor();
}
