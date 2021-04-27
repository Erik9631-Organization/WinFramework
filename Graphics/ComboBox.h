#pragma once
#include "Panel.h"
#include "SimpleBorder.h"
#include "ComboSelection.h"
#include "ComboBoxStateSubscriber.h"
#include "DefaultComboBoxBehavior.h"

class Button;
class DefaultComboBoxBehavior;

class ComboBox : public Panel
{
private:
	ComboSelection selections;
	Button* button;
	DefaultComboBoxBehavior behavior;
public:
	ComboBox();
	ComboBox(std::string componentName);
	ComboBox(int x, int y, int width, int height, std::string componentName);
	void SetComboButton(Button* button);
	std::wstring GetText();
	void SetText(std::wstring text);
	MouseStateSubject& CreateComboElement(std::wstring comboElementText);
	void Upack();
	void Pack();
};

