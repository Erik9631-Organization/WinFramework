#pragma once
#include "Component.h"
#include "SimpleBorder.h"
#include "Text.h"
#include "Background.h"
#include "CheckboxBehavior.h"

class Checkbox : public Component, public CheckboxStateSubject
{
private:
	SimpleBorder border;
	SimpleBorder checkboxBorder;
	Background background;
	CheckBoxBehavior checkboxBehavior;
	bool checked = false;

	Text checkBoxChar;
	Text text;
public:
	void SetText(std::wstring text) override;
	void Check();
	std::wstring GetText() override;
	void SetChecked(bool state);
	bool IsChecked();
	Checkbox();
	Checkbox(string name);
	Checkbox(int x, int y, int width, int height, string name);

	// Inherited via CheckboxStateSubject
	virtual void AddCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber) override;
	virtual void RemoveCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber) override;
	virtual void NotifyOnChecked(EventCheckboxStateInfo info) override;
};

