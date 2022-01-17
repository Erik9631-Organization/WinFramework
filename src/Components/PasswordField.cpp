#include "PasswordField.h"
#include "Graphics/Text.h"

PasswordField::PasswordField() : PasswordField("")
{

}

PasswordField::PasswordField(int x, int y, int width, int height, string windowName) : Component(x, y, width, height, windowName), text("Arial"), behavior(*this)
{
	text.SetFontSize(16.0);
	text.SetColor(Color::Black);
	border.SetColor(Color::MakeARGB(255, 100, 100, 100));
	border.SetThickness(1.0f);
	background.SetColor(Color(200, 200, 200));

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
	Repaint();
}

wstring PasswordField::GetText()
{
	return realText;
}


Color PasswordField::GetBackgroundColor()
{
	return background.GetColor();
}

void PasswordField::SetBackgroundColor(Color color)
{
	background.SetColor(color);
	Repaint();
}
