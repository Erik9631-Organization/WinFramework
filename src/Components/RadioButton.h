#pragma once
#include "UiElement.h"
#include "Graphics/CircleBorder.h"
#include "Graphics/SimpleBorder.h"
#include "Graphics/RadioButtonGraphics.h"
#include "Graphics/Text.h"
#include "RadioButtonBehavior.h"
#include <vector>
#include <memory>
#include "Events/RadioButtonStateSubject.h"
#include "Border.h"
#include "Text2.h"
#include "RadioCircle.h"

class RadioButton : public UiElement, public RadioButtonStateSubject
{
private:
	Border border;
	RadioCircle radioCircle;
	RadioButtonBehavior behavior;
	Text2 text;
	
	// Background background;
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
	RadioButton(float x, float y, float width, float height, std::string componentName);

	// Inherited via RadioButtonStateSubject
	virtual void NotifyOnRadioButtonSelected(EventRadioButtonStateInfo e) override;
	virtual void AddRadioButtonStateSubscriber(RadioButtonStateSubscriber& subscriber) override;
	virtual void RemoveRadiobuttonStateSubscriber(RadioButtonStateSubscriber& subscriber) override;
};

