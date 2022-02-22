#include "Label.h"

Label::Label(std::string name) : UiElement(name), text("Arial")
{
}

Label::Label() : text("Arial")
{
}

Label::Label(int x, int y, int width, int height, std::string name) : UiElement(x, y, width, height, name), text("Arial")
{
	background.SetColor({30, 30, 30});
	AddRenderable(background);
	AddRenderable(text);
}

void Label::SetBackground(Vector3 color)
{
	background.SetColor(color);
	//Repaint();
}

Vector3 Label::GetBackground()
{
	return background.GetColor();
}

void Label::SetText(std::wstring str)
{
	text.SetText(str);
	//Repaint();
}

std::wstring Label::GetText()
{
	return text.GetText();
}