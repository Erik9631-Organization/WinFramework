#include "TextInput.h"
using namespace std;

TextInput::TextInput() : TextInput(0, 0, 0, 0, "")
{

}

TextInput::TextInput(int x, int y, int width, int height, string windowName) : text("Arial"), border(), background(), inputBehavior(*this)
{
    SetPosition(x, y, false);
    SetSize(width, height, false);

	text.SetFontSize(12.0);
	text.SetColor({0, 0, 0});
	border.SetColor({100, 100, 100});
	border.SetThickness(1.0f);
	background.SetColor({200, 200, 200});

    renderBehavior.AddRenderCommander(background);
    renderBehavior.AddRenderCommander(border);
    renderBehavior.AddRenderCommander(text);
}

TextInput::TextInput(string name) : TextInput(0, 0, 0, 0, name)
{
}

void TextInput::SetText(wstring text)
{
	this->text.SetText(text);
	//Repaint();
}

wstring TextInput::GetText()
{
	return text.GetText();
}

Vector3 TextInput::GetBackgroundColor()
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

void TextInput::SetBackgroundColor(Vector3 color)
{
	background.SetColor(color);
	//Repaint();
}
