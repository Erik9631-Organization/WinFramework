#include "Button.h"
#include "CoreWindowFrame.h"
void Button::SetBorderStyle(Border* border)
{
	this->border = border;
}

void Button::SetBorderColor(COLORREF color)
{
	border->SetBorderColor(color);
}

void Button::SetBorderThickness(float thickness)
{
	border->SetBorderThickness(thickness);
}

void Button::Paint(Graphics& graphics)
{
	Component::Paint(graphics);
	border->Paint(graphics);
}

Button::Button(int x, int y, int width, int height)
{
	SetSize(width, height);
	SetPosition(x, y);
	SetBorderStyle(new Border(size, pos));
	componentType = "Button";
}


Button::~Button()
{
	delete pen;
}
