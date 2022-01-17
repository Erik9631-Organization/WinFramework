#include "ComboBox.h"
#include "Components/Button.h"
#include "Behavior/DefaultComboBoxBehavior.h"
#include "Components/CoreWindowFrame.h"
#include "ComboElement.h"

bool ComboBox::IsPacked()
{
	return isPacked;
}

ComboBox::ComboBox() : ComboBox("")
{

}

ComboBox::ComboBox(std::string componentName) : ComboBox(0, 0, 0, 0, componentName)
{

}

ComboBox::ComboBox(int x, int y, int width, int height, std::string componentName) : Panel(x, y, width, height, componentName),
	selections(),
	button(new Button(0, 0, width, height)),
	behavior(*this, button, selections)
{
	Add(*button);
}

void ComboBox::SetComboButton(Button* button)
{
	this->button = button;
}

std::wstring ComboBox::GetText()
{
	return button->GetText();
}

void ComboBox::SetText(std::wstring text)
{
	button->SetText(text);
}

MouseStateSubject& ComboBox::CreateComboElement(std::wstring comboElementText, std::any value)
{
	MouseStateSubject& subject = selections.CreateComboElement(comboElementText, value);
	if (selections.GetElements().size() == 1)
		SetText(selections.GetElements().at(0)->GetText());
	return subject;
}

void ComboBox::Upack()
{
	int windowPosX = GetRoot().GetX();
	int windowPosY = GetRoot().GetY();

	int comboSelectionX = GetAbsoluteX() + windowPosX;
	int comboSelectionY = GetAbsoluteY() + windowPosY + GetHeight();

	selections.CreateGui(comboSelectionX, comboSelectionY, GetWidth(), GetHeight());
	isPacked = false;
}

void ComboBox::Pack()
{
	selections.CloseGui();
	isPacked = true;
}

ComboElement& ComboBox::GetSelectedElement()
{
	return selections.GetSelectedElement();
}

void ComboBox::NotifyOnComboBoxOpened(EventComboBoxStateInfo e)
{
	behavior.NotifyOnComboBoxOpened(e);
}

void ComboBox::NotifyOnComboBoxClosed(EventComboBoxStateInfo e)
{
	behavior.NotifyOnComboBoxClosed(e);
}

void ComboBox::NotifyOnSelectionChanged(EventComboBoxStateInfo e)
{
	behavior.NotifyOnSelectionChanged(e);
}

void ComboBox::AddComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber)
{
	behavior.AddComboBoxStateSubscriber(subscriber);
}

void ComboBox::RemoveComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber)
{
	behavior.RemoveComboBoxStateSubscriber(subscriber);
}
