#include "TextInput.h"

TextInput::TextInput() : TextInput(0, 0, 0, 0, "")
{

}

TextInput::TextInput(int x, int y, int width, int height, string windowName) : text("Arial"), border(), background(), inputBehavior(*this)
{
	SetPosition(x, y);
	SetSize(width, height);

	text.SetFontSize(12.0);
	text.SetColor(Color::Black);
	border.SetColor(Color::MakeARGB(255, 100, 100, 100));
	border.SetThickness(1.0f);
	background.SetColor(Color(200, 200, 200));

	renderBehavior.AddRenderable(background);
	renderBehavior.AddRenderable(border);
	renderBehavior.AddRenderable(text);
}

TextInput::TextInput(string name) : TextInput(0, 0, 0, 0, name)
{
}

void TextInput::SetText(wstring text)
{
	this->text.SetText(text);
	Repaint();
}

wstring TextInput::GetText()
{
	return text.GetText();
}

Color TextInput::GetBackgroundColor()
{
	return background.GetColor();
}

void TextInput::SetMultiline(bool state)
{
	inputBehavior.SetMultiline(state);
}

bool TextInput::IsMultiLine()
{
	return inputBehavior.IsMultiLine();
}

void TextInput::SetBackgroundColor(Color color)
{
	background.SetColor(color);
	Repaint();
}
