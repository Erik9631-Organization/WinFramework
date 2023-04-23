#include "RadioButton.h"
#include "EventRadioButtonStateInfo.h"
using namespace std;

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

	radioCircle.SetFillEnabled(checked);
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

const wstring & RadioButton::GetText()
{
	return text.GetText();
}

RadioButton::RadioButton() : RadioButton("")
{

}

RadioButton::RadioButton(std::string name) : RadioButton(0, 0, 0, 0, name)
{

}

RadioButton::RadioButton(float x, float y, float width, float height, string componentName) :
    UiElement(x, y, width, height, componentName),
    behavior(*this),
    border(*this),
    text(*this),
    radioCircle(*this)
{
	border.SetColor({0, 0, 0, 255});
    radioCircle.SetRadius(7.5f);
	radioCircle.GetScales().SetCalculateFromCenterX(false);
    radioCircle.GetScales().SetCalculateFromCenterY(true);
    radioCircle.GetScales().SetUnitTypePosX(GraphicsScaling::Percentual);
    radioCircle.GetScales().SetUnitTypePosY(GraphicsScaling::Percentual);
    radioCircle.SetX(0.1f);

    // TODO Fix units. Potential issue if differet units are used

	text.SetFontSize(12.0f);
	text.SetFontLineAlignment(FontAlignment::FontAlignmentCenter);
    text.SetFontAlignment(FontAlignment::FontAlignmentCenter);
    text.GetScales().SetUnitTypePosX(GraphicsScaling::Percentual);
    text.GetScales().SetUnitTypePosY(GraphicsScaling::Percentual);
	text.SetText(L"");
    text.SetX(0.1f);
    text.GetX();
    border.SetVisible(true);
	SetChecked(false);
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

void RadioButton::SetBorder(bool state)
{
    border.SetVisible(state);
}
