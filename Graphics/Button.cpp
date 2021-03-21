#include "Button.h"
#include "CoreWindowFrame.h"
#include "RenderEventInfo.h"
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
	return background.GetColor();
}

Gdiplus::Color Button::GetBorderColor(Color color)
{
	return border.GetColor();
}

void Button::SetBackgroundColor(Color color)
{
	background.SetColor(color);
	Repaint();
}

void Button::SetBorderThickness(float thickness)
{
	border.SetThickness(thickness);
	Repaint();
}


Button::Button(int x, int y, int width, int height) : text("Arial"), mouseGraphicalState(*this)
{
	SetSize(width, height);
	SetPosition(x, y);
	componentType = "Button";

	border.SetColor(Color::MakeARGB(100, 0, 0, 0));
	border.SetThickness(1.0f);

	background.SetColor(Color(30, 30, 30));
	text.SetPercentualPosition(PointF(0.5f, 0.5f));
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
