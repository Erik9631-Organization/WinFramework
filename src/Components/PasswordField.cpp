#include "PasswordField.h"
#include "Graphics/Text.h"
using namespace std;

PasswordField::PasswordField() : PasswordField("")
{

}

PasswordField::PasswordField(int x, int y, int width, int height, string windowName) : UiElement(x, y, width, height, windowName), text("Arial"), behavior(*this)
{
	text.SetFontSize(16.0);
	text.SetColor({0, 0, 0});
	border.SetColor({100, 100, 100});
	border.SetThickness(1.0f);
	//background.SetBackgroundColor({200, 200, 200});

    //renderBehavior.AddRenderCommander(background);
    renderBehavior.AddRenderCommander(border);
    renderBehavior.AddRenderCommander(text);
	behavior.SetMultiline(false);
}

PasswordField::PasswordField(string name) : PasswordField(0, 0, 0, 0, name)
{
}

void PasswordField::SetText(wstring text)
{
	wstring hiddenText;
	realText = text;
	hiddenText.insert(0, text.size(), '*');
	this->text.SetText(hiddenText);
	//Repaint();
}

void PasswordField::SetBackgroundColor(glm::vec3 color)
{
	//background.SetBackgroundColor(color);
	//Repaint();
}

const wstring &PasswordField::GetText()
{
    return text.GetText();
}

const glm::ivec4 &PasswordField::GetBackgroundColor()
{
    return {0,0,0,0};
}

void PasswordField::SetBackgroundColor(const glm::ivec4 &color)
{

}
