#include "Label.h"

Label::Label(const std::string &name) : Label(0, 0, 0, 0, name)
{
}

Label::Label() : Label(0, 0, 0, 0, "")
{
}

Label::Label(int x, int y, int width, int height, std::string name) : UiElement(x, y, width, height, name),
        text(*this),
        background(*this)
{
	background.SetColor({30, 30, 30, 255});
    text.SetColor({255, 255, 255, 255});
    text.SetFontAlignment(FontAlignment::FontAlignmentCenter);
    text.SetFontLineAlignment(FontAlignment::FontAlignmentCenter);
}


void Label::SetText(std::wstring str)
{
	text.SetText(str);
}

const std::wstring & Label::GetText()
{
	return text.GetText();
}

void Label::SetBackground(const glm::ivec4 &color)
{
    background.SetColor(color);
}

const glm::ivec4 &Label::GetBackground()
{
    return background.GetColor();
}