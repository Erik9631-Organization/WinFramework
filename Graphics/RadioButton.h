#pragma once
#include "Component.h"
#include "CircleBorder.h"
#include "SimpleBorder.h"
#include "RadioButtonGraphics.h"
#include "Text.h"
#include "RadioButtonBehavior.h"
#include <vector>
#include <memory>
#include "RadioButtonStateSubject.h"

class RadioButton : public Component, public RadioButtonStateSubject
{
private:
	SimpleBorder border;
	RadioButtonGraphics radioButtonGraphics;
	RadioButtonBehavior behavior;
	Text text;
	
	Background background;
	//radioButtonBehavior
	bool checked = false;
public:
	void Check();
	bool IsChecked();
	void SetChecked(bool state);
	void AddToGroup(RadioButton& button);
	void SetGroup(std::shared_ptr<std::vector<std::reference_wrapper<RadioButton>>> group);
	void UnGroup();
	void SetText(std::wstring text) override;
	std::wstring GetText() override;

	RadioButton();
	RadioButton(std::string name);
	RadioButton(int x, int y, int width, int height, string componentName);

	// Inherited via RadioButtonStateSubject
	virtual void NotifyOnRadioButtonSelected(EventRadioButtonStateInfo e) override;
	virtual void AddRadioButtonStateSubscriber(RadioButtonStateSubscriber& subscriber) override;
	virtual void RemoveRadiobuttonStateSubscriber(RadioButtonStateSubscriber& subscriber) override;
};

