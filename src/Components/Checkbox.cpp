#include "Checkbox.h"
#include "EventTypes/EventCheckboxStateInfo.h"

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
	if (state == true)
	{
		checkBoxChar.SetText(L"✓");
		checkboxBehavior.NotifyOnChecked(EventCheckboxStateInfo(this, true));
	}

	else
	{
		checkBoxChar.SetText(L"");
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

Checkbox::Checkbox(int x, int y, int width, int height, string name) : UiElement(x, y, width, height, name), checkBoxChar("Arial"), text("Arial"), checkboxBehavior(*this)
{
	border.SetColor({0, 0, 0});
	border.SetThickness(1.0f);
	background.SetColor({0, 0, 0, 0});

	checkboxBorder.SetColor({0, 0, 0});
	checkboxBorder.SetScalingTypeWidth(Decimal);
	checkboxBorder.SetScalingTypeHeight(Decimal);

	checkboxBorder.DrawFromCenterY(true);

	checkboxBorder.SetWidth(15.0f);
	checkboxBorder.SetHeight(15.0f);

    checkboxBorder.SetX(0.02f);
    checkboxBorder.SetY(0.5f);

	checkBoxChar.SetLineAlignment(StringAlignment::StringAlignmentCenter);
	checkBoxChar.SetAlignment(StringAlignment::StringAlignmentCenter);
	checkBoxChar.SetScalingTypeY(Percentual);
	checkBoxChar.SetScalingTypeX(Decimal);
	checkBoxChar.SetPosition({10.0f, 0.51f});
	checkBoxChar.SetText(L"");
	checkBoxChar.SetColor({0, 0, 0});

	text.SetLineAlignment(StringAlignment::StringAlignmentCenter);
	text.SetColor({0, 0, 0});
	text.SetScalingTypeY(Percentual);
	text.SetScalingTypeX(Decimal);

	text.SetPosition({20.0f, 0.51f});

    AddRenderCommander(background);
    AddRenderCommander(border);
    AddRenderCommander(checkboxBorder);
    AddRenderCommander(checkBoxChar);
    AddRenderCommander(text);
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
