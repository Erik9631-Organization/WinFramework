#include "Button.h"
#include "CoreWindowFrame.h"
#include "RenderEventInfo.h"
void Button::SetBorderColor(COLORREF color)
{
	border.SetColor(color);
}

void Button::SetBackgroundColor(COLORREF color)
{
	background.SetColor(color);
}

void Button::SetBorderThickness(float thickness)
{
	border.SetThickness(thickness);
}


Button::Button(int x, int y, int width, int height)
{
	SetSize(width, height);
	SetPosition(x, y);
	componentType = "Button";

	border.SetColor(Color::Red);
	border.SetThickness(1);

	background.SetColor(Color(33, 150, 243));

	renderBehavior.AddRenderable(background);
	renderBehavior.AddRenderable(border);
}


Button::~Button()
{

}
