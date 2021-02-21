#include "Label.h"

Label::Label(std::string name) : Component(name), text("Arial")
{
}

Label::Label() : text("Arial")
{
}

Label::Label(int x, int y, int width, int height, std::string name) : Component(x, y, width, height, name), text("Arial")
{
	background.SetColor(Color::MakeARGB(255, 30, 30, 30));
	AddRenderable(background);
	AddRenderable(text);
}

void Label::SetBackground(Gdiplus::Color color)
{
	background.SetColor(color);
}

void Label::GetBackground(Gdiplus::Color color)
{
	background.GetColor();
}

void Label::SetText(std::wstring str)
{
	text.SetText(str);
	Repaint();
}

std::wstring Label::GetText()
{
	return text.GetText();
}
