#include "Button.h"
#include "CoreWindowFrame.h"
#include "EventTypes/RenderEventInfo.h"
void Button::SetBorderColor(COLORREF color)
{
	border.SetColor(color);
	Repaint();
}

void Button::SetBackgroundColor(COLORREF color)
{
	background.SetColor(color);
	Repaint();
}

void Button::SetBorderColor(Color color)
{
	border.SetColor(color);
	Repaint();
}

Gdiplus::Color Button::GetBackgroundColor()
{
    return buttonBehavior.GetStandardColor();
}

Gdiplus::Color Button::GetBorderColor()
{
	return border.GetColor();
}

void Button::SetBorderThickness(float thickness)
{
	border.SetThickness(thickness);
	Repaint();
}


Button::Button(int x, int y, int width, int height) : text("Arial"), buttonBehavior(*this)
{
	SetSize(width, height);
	SetPosition(x, y);
	componentType = "Button";

	border.SetColor(Color::MakeARGB(100, 0, 0, 0));
	border.SetThickness(1.0f);

	background.SetColor({30, 30, 30});
	SetBackgroundColor({30, 30, 30});

	text.SetScalingTypeY(Percentual);
	text.SetScalingTypeY(Percentual);

	text.SetPosition({0.5f, 0.5f});
	text.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
	text.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);

	renderBehavior.AddRenderable(background);
	renderBehavior.AddRenderable(border);
	renderBehavior.AddRenderable(text);
}

void Button::SetText(std::wstring text)
{
	this->text.SetText(text);
	Repaint();
}

std::wstring Button::GetText()
{
	return text.GetText();
}


Button::~Button()
{

}

void Button::SetOnHoverColor(Gdiplus::Color color)
{
    buttonBehavior.SetOnHoverColor(color);
}

void Button::SetOnClickColor(Gdiplus::Color color)
{
    buttonBehavior.SetOnClickColor(color);
}

void Button::SetBackgroundColor(Color statelessColor)
{
    buttonBehavior.SetStatelessColor(statelessColor);
}

void Button::SetColor(Gdiplus::Color color)
{
    background.SetColor(color);
    Repaint();
}

Color Button::GetOnClickColor()
{
    return buttonBehavior.GetOnClickColor();
}

Color Button::GetOnHoverColor()
{
    return buttonBehavior.GetOnHoverColor();
}

Gdiplus::Color Button::GetColor()
{
    return background.GetColor();
}
