#include "TextInput.h"
using namespace std;

TextInput::TextInput(int x, int y, int width, int height, string windowName) : UiElement(x, y, width, height, windowName),
    text(*this),
    border(*this),
    background(*this),
    inputBehavior(*this)
{

    text.SetFontSize(12.0);
    text.SetColor({0, 0, 0, 255});
    border.SetColor({100, 100, 100, 255});
    background.SetColor({200, 200, 200, 255});
    text.SetFontLineAlignment(FontAlignment::FontAlignmentFar);
    text.SetFontAlignment(FontAlignment::FontAlignmentNear);
    text.GetScales().SetCalculateFromCenterX(false);
    text.GetScales().SetCalculateFromCenterY(false);
    text.GetScales().SetUnitTypePosY(GraphicsScaling::Percentual);
    text.SetY(0.3f);
    auto viewPortSize = UiElement::GetSize();
    viewPortSize.x += borderWidth;
    viewPortSize.y += borderWidth;
    UiElement::SetViewportPosition(UiElement::GetPosition());
    UiElement::SetViewportSize(viewPortSize);
}

TextInput::TextInput() : TextInput(0, 0, 0, 0, "")
{

}

TextInput::TextInput(string name) : TextInput(0, 0, 0, 0, name)
{

}

void TextInput::SetText(wstring text)
{
	this->text.SetText(text);
}


const glm::ivec4 & TextInput::GetBackgroundColor()
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

void TextInput::SetBackgroundColor(const glm::ivec4 &color)
{
	background.SetColor(color);
}

const wstring &TextInput::GetText()
{
    return text.GetText();
}

void TextInput::SetPosition(glm::vec4 position)
{
    UiElement::SetPosition(position);
    UiElement::SetViewportPosition(position);
}

void TextInput::SetSize(const glm::vec4 &size, bool emit)
{
    UiElement::SetSize(size, emit);
    auto viewportSize = size;
    viewportSize.x += borderWidth;
    viewportSize.y += borderWidth;
    UiElement::SetViewportSize(viewportSize);
}
