#include "RadioButton.h"

void RadioButton::Check()
{
	if (IsChecked())
		SetChecked(false);
	else
		SetChecked(true);
}

bool RadioButton::IsChecked()
{
	return this->checked;
}

void RadioButton::SetChecked(bool checked)
{
	this->checked = checked;
	radioButtonGraphics.SetFillEnabled(checked);
	Repaint();
}

void RadioButton::AddToGroup(RadioButton& button)
{
	behavior.Group(button);
}

void RadioButton::SetGroup(std::shared_ptr<std::vector<std::reference_wrapper<RadioButton>>> group)
{
	behavior.SetGroup(group);
}

void RadioButton::UnGroup()
{
	behavior.UnGroup();
}

void RadioButton::SetText(std::wstring text)
{
	this->text.SetText(text);
}

std::wstring RadioButton::GetText()
{
	return text.GetText();
}

RadioButton::RadioButton() : RadioButton("")
{

}

RadioButton::RadioButton(std::string name) : RadioButton(0, 0, 0, 0, name)
{

}

RadioButton::RadioButton(int x, int y, int width, int height, string componentName) : Component(x, y, width, height, componentName), text("Arial"), behavior(*this)
{
	border.SetColor(Color::Black);
	border.SetThickness(1.0f);
	radioButtonGraphics.SetRadius(15.0f);
	radioButtonGraphics.SetFillPadding(5.0f);
	radioButtonGraphics.SetScalingType(1);
	radioButtonGraphics.SetPercentualPosition(PointF(0.2f, 0.5f));
	radioButtonGraphics.SetDrawFromCenter(true);

	text.SetColor(Gdiplus::Color::Black);
	text.SetFontSize(12.0f);
	text.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
	text.SetPercentualPosition(PointF(0.2f, 0.52f));
	text.SetPosition(PointF(10.0f, 0.0f));
	text.SetText(L"Radio");
	SetChecked(false);

	AddRenderable(radioButtonGraphics);
	AddRenderable(border);
	AddRenderable(text);
}
