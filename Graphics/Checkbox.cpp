#include "Checkbox.h"
#include "EventCheckboxStateInfo.h"

void Checkbox::SetText(std::wstring text)
{
	this->text.SetText(text);
	Repaint();
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
		checkboxBehavior.NotifyOnChecked(EventCheckboxStateInfo(std::make_any<Checkbox*>(this), true));
	}

	else
	{
		checkBoxChar.SetText(L"");
		checkboxBehavior.NotifyOnChecked(EventCheckboxStateInfo(std::make_any<Checkbox*>(this), false));
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

Checkbox::Checkbox(int x, int y, int width, int height, string name) : Component(x, y, width, height, name), checkBoxChar("Arial"), text("Arial"), checkboxBehavior(*this)
{
	border.SetColor(Color::Black);
	border.SetThickness(1.0f);
	background.SetColor(Color::Transparent);

	checkboxBorder.SetColor(Color::Black);
	checkboxBorder.SetScalingType(1);
	checkboxBorder.SetVerticalCentering(true);

	checkboxBorder.GetSize().Width = 15.0f;
	checkboxBorder.GetSize().Height = 15.0f;

	checkboxBorder.GetPercentualPosition().Y = 0.5f;
	checkboxBorder.GetPercentualPosition().X = 0.0f;

	checkBoxChar.SetLineAlignment(StringAlignment::StringAlignmentCenter);
	checkBoxChar.SetAlignment(StringAlignment::StringAlignmentCenter);
	checkBoxChar.SetPercentualPosition(PointF(0, 0.51f));
	checkBoxChar.SetPosition(PointF(10.0f, 0.0f));
	checkBoxChar.SetText(L"");
	checkBoxChar.SetColor(Color::Black);

	text.SetLineAlignment(StringAlignment::StringAlignmentCenter);
	text.SetColor(Color::Black);
	text.SetPercentualPosition(PointF(0, 0.51f));
	text.SetPosition(PointF(20.0f, 0.0f));

	AddRenderable(background);
	AddRenderable(border);
	AddRenderable(checkboxBorder);
	AddRenderable(checkBoxChar);
	AddRenderable(text);
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
