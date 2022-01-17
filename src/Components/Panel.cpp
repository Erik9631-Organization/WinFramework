#include "Panel.h"

Panel::Panel() : Panel("")
{
}

Panel::Panel(std::string name) : Panel(0, 0, 0, 0, name)
{
}

Panel::Panel(int x, int y, int width, int height, std::string name) : Component(x, y, width, height, name)
{
	border.SetColor(Gdiplus::Color::Black);
	AddRenderable(border);
}
