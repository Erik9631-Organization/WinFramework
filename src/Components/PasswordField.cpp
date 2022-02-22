#include "PasswordField.h"
#include "Graphics/Text.h"

PasswordField::PasswordField() : PasswordField("")
{

}

PasswordField::PasswordField(int x, int y, int width, int height, string windowName) : UiElement(x, y, width, height, windowName), text("Arial"), behavior(*this)
{
	text.SetFontSize(16.0);
	text.SetColor({0, 0, 0});
	border.SetColor({100, 100, 100});
	border.SetThickness(1.0f);
	background.SetColor({200, 200, 200});

	renderBehavior.AddRenderable(background);
	renderBehavior.AddRenderable(border);
	renderBehavior.AddRenderable(text);
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

wstring PasswordField::GetText()
{
	return realText;
}


Vector3 PasswordField::GetBackgroundColor()
{
	return background.GetColor();
}

void PasswordField::SetBackgroundColor(Vector3 color)
{
	background.SetColor(color);
	//Repaint();
}