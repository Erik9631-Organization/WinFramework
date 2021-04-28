#pragma once
#include "Panel.h"
#include "SimpleBorder.h"
#include "ComboSelection.h"
#include "ComboBoxStateSubscriber.h"
#include "ComboBoxStateSubject.h"
#include "DefaultComboBoxBehavior.h"
#include <any>

class Button;
class DefaultComboBoxBehavior;

class ComboBox : public Panel, public ComboBoxStateSubject
{
private:
	ComboSelection selections;
	Button* button;
	DefaultComboBoxBehavior behavior;
	bool isPacked = true;
public:
	bool IsPacked();
	ComboBox();
	ComboBox(std::string componentName);
	ComboBox(int x, int y, int width, int height, std::string componentName);
	void SetComboButton(Button* button);
	std::wstring GetText();
	void SetText(std::wstring text);
	MouseStateSubject& CreateComboElement(std::wstring comboElementText, std::any value);
	void Upack();
	void Pack();
	ComboElement& GetSelectedElement();

	// Inherited via ComboBoxStateSubject
	virtual void NotifyOnComboBoxOpened(EventComboBoxStateInfo e) override;
	virtual void NotifyOnComboBoxClosed(EventComboBoxStateInfo e) override;
	virtual void NotifyOnSelectionChanged(EventComboBoxStateInfo e) override;
	virtual void AddComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber) override;
	virtual void RemoveComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber) override;
};

