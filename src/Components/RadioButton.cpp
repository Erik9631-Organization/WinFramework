#include "RadioButton.h"
#include "EventTypes/EventRadioButtonStateInfo.h"

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
	if (this->checked == checked)
		return;
	this->checked = checked;
	behavior.NotifyOnRadioButtonSelected(EventRadioButtonStateInfo(checked, this));

	radioButtonGraphics.SetFillEnabled(checked);
	//Repaint();
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
	//Repaint();
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

RadioButton::RadioButton(int x, int y, int width, int height, string componentName) : UiElement(x, y, width, height, componentName), text("Arial"), behavior(*this)
{
	border.SetColor({0, 0, 0});
	border.SetThickness(1.0f);
	radioButtonGraphics.SetFillEnabled(false);
    radioButtonGraphics.SetDiameter(15.0f);
	radioButtonGraphics.SetFillPadding(5.0f);
	radioButtonGraphics.SetDrawFromCenterY(true);
	radioButtonGraphics.SetDrawFromCenterX(true);
	radioButtonGraphics.SetScalingTypeWidth(Decimal);
	radioButtonGraphics.SetScalingTypeHeight(Decimal);
	radioButtonGraphics.SetY(0.5f);
	radioButtonGraphics.SetX(0.1f);

	text.SetColor({0, 0, 0});
	text.SetFontSize(12.0f);
	text.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
	text.SetScalingTypeX(Percentual);
	text.SetScalingTypeY(Percentual);
	text.SetPosition({0.23f, 0.52f});
	text.SetText(L"Radio");
	SetChecked(false);

	AddRenderable(radioButtonGraphics);
	AddRenderable(border);
	AddRenderable(text);
}

void RadioButton::NotifyOnRadioButtonSelected(EventRadioButtonStateInfo e)
{
	behavior.NotifyOnRadioButtonSelected(e);
}

void RadioButton::AddRadioButtonStateSubscriber(RadioButtonStateSubscriber& subscriber)
{
	behavior.AddRadioButtonStateSubscriber(subscriber);
}

void RadioButton::RemoveRadiobuttonStateSubscriber(RadioButtonStateSubscriber& subscriber)
{
	behavior.RemoveRadiobuttonStateSubscriber(subscriber);
}
