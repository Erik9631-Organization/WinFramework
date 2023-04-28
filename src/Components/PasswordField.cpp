#include "PasswordField.h"
#include "Graphics/Text.h"
using namespace std;

PasswordField::PasswordField() : PasswordField("")
{

}

PasswordField::PasswordField(int x, int y, int width, int height, string windowName) : UiElement(x, y, width, height, windowName),
    text(*this),
    behavior(*this),
    background(*this),
    border(*this)
{
	text.SetFontSize(16.0);
	text.SetColor({0, 0, 0, 255});
	border.SetColor({100, 100, 100, 255});
	background.SetColor({200, 200, 200,255});
	behavior.SetMultiline(false);
    text.SetFontLineAlignment(FontAlignment::FontAlignmentNear);
    text.SetFontAlignment(FontAlignment::FontAlignmentNear);
    text.GetScales().SetCalculateFromCenterX(false);
    text.GetScales().SetCalculateFromCenterY(false);
    text.GetScales().SetUnitTypePosY(GraphicsScaling::Percentual);
    auto viewPortSize = UiElement::GetSize();
    viewPortSize.x += borderWidth;
    viewPortSize.y += borderWidth;
    UiElement::SetViewportPosition(UiElement::GetPosition());
    UiElement::SetViewportSize(viewPortSize);
}

PasswordField::PasswordField(string name) : PasswordField(0, 0, 0, 0, std::move(name))
{

}

void PasswordField::SetText(wstring text)
{
	wstring hiddenText;
	realText = text;
	hiddenText.insert(0, text.size(), '*');
	this->text.SetText(hiddenText);
}

void PasswordField::SetBackgroundColor(const glm::vec4 &color)
{
    background.SetColor(color);
}

const wstring &PasswordField::GetText()
{
    return text.GetText();
}

const glm::ivec4 &PasswordField::GetBackgroundColor()
{
    return background.GetColor();
}

void PasswordField::SetPosition(const glm::vec3 &position, bool emit)
{
    UiElement::SetPosition(position, emit);
    UiElement::SetViewportPosition(position);
}

void PasswordField::SetSize(const glm::vec4 &size, bool emit)
{
    UiElement::SetSize(size, emit);
    auto viewportSize = size;
    viewportSize.x += borderWidth;
    viewportSize.y += borderWidth;
    UiElement::SetViewportSize(viewportSize);

}

void PasswordField::SetBackgroundColor(const glm::ivec4 &color)
{
    background.SetColor(color);
}
