#include "ComboBox.h"
#include "Button.h"
#include "DefaultComboBoxBehavior.h"
#include "CoreWindowFrame.h"
#include "ComboElement.h"

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

MouseStateSubject& ComboBox::CreateComboElement(std::wstring comboElementText)
{
	MouseStateSubject& subject = selections.CreateComboElement(comboElementText);
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

	CoreWindowFrame::ConsoleWrite(to_string(comboSelectionX) + " " + to_string(comboSelectionY));

	selections.CreateGui(comboSelectionX, comboSelectionY, GetWidth(), GetHeight());
}

void ComboBox::Pack()
{
	selections.CloseGui();
}
