#include "Checkbox.h"
#include "EventCheckboxStateInfo.h"
using namespace std;

void Checkbox::SetText(std::wstring text)
{
	this->text.SetText(text);
	//Repaint();
}

void Checkbox::Check()
{
	if (checked == true)
		SetChecked(false);
	else
		SetChecked(true);
}

std::wstring Checkbox::GetText()
{
	return text.GetText();
}

void Checkbox::SetChecked(bool state)
{
	if (state)
	{
		//checkBoxChar.SetText(L"✓");
		checkboxBehavior.NotifyOnChecked(EventCheckboxStateInfo(this, true));
	}

	else
	{
		//checkBoxChar.SetText(L"");
		checkboxBehavior.NotifyOnChecked(EventCheckboxStateInfo(this, false));
	}

	checked = state;
}

bool Checkbox::IsChecked()
{
	return checked;
}

Checkbox::Checkbox() : Checkbox(0, 0, 0, 0, "")
{
}

Checkbox::Checkbox(string name) : Checkbox(0, 0, 0, 0, name)
{
}

Checkbox::Checkbox(int x, int y, int width, int height, string name) : UiElement(x, y, width, height, name) ,
        checkboxBehavior(*this),
        border(*this),
        text(this),
        checkboxGraphics(*this)
{
	border.SetColor({0, 0, 0, 255});
    text.SetFontSize(12.0f);
    text.SetFontLineAlignment(FontAlignment::FontAlignmentCenter);
    text.SetFontAlignment(FontAlignment::FontAlignmentCenter);
    text.GetScales().SetUnitTypePosX(GraphicsScaling::Percentual);
    text.GetScales().SetUnitTypePosY(GraphicsScaling::Percentual);

	text.SetX(0.1f);
}

void Checkbox::AddCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber)
{
	checkboxBehavior.AddCheckboxStateSubscriber(subscriber);
}

void Checkbox::RemoveCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber)
{
	checkboxBehavior.RemoveCheckboxStateSubscriber(subscriber);
}

void Checkbox::NotifyOnChecked(EventCheckboxStateInfo info)
{
	checkboxBehavior.NotifyOnChecked(info);
}
