#include "Label.h"

Label::Label(std::string name) : UiElement(name), text("Arial")
{
}

Label::Label() : text("Arial")
{
}

Label::Label(int x, int y, int width, int height, std::string name) : UiElement(x, y, width, height, name), text("Arial")
{
	//background.SetColor({30, 30, 30});
    //AddRenderCommander(background);
    AddRenderCommander(text);
}

void Label::SetBackground(glm::vec3 color)
{
	//background.SetColor(color);
	//Repaint();
}

glm::vec3 Label::GetBackground()
{
	return {0, 0, 0}; //background.GetColor();
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
