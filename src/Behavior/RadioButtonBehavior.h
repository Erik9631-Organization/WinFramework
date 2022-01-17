#pragma once
#include "Events/MouseStateSubscriber.h"
#include <vector>
#include <memory>
#include "Events/RadioButtonStateSubject.h"

class RadioButton;

class RadioButtonBehavior : MouseStateSubscriber, public RadioButtonStateSubject
{
private:
	RadioButton& associatedRadioButton;
	std::shared_ptr<std::vector<std::reference_wrapper<RadioButton>>> group;
	std::vector<std::reference_wrapper<RadioButtonStateSubscriber>> subscribers;
	void RemoveFromGroup(RadioButton& button);

    void OnMouseCaptured(EventMouseStateInfo e) override;

public: 
	RadioButtonBehavior(RadioButton& button);
	void Group(RadioButton& button);
	void UnGroup();
	void SetGroup(std::shared_ptr<std::vector<std::reference_wrapper<RadioButton>>> group);


	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;

	virtual void OnMouseUp(EventMouseStateInfo e) override;

	virtual void OnMousePressed(EventMouseStateInfo e) override;

	virtual void OnMouseMove(EventMouseStateInfo e) override;

	virtual void OnMouseEntered(EventMouseStateInfo e) override;

	virtual void OnMouseLeft(EventMouseStateInfo e) override;


	// Inherited via RadioButtonStateSubject
	virtual void NotifyOnRadioButtonSelected(EventRadioButtonStateInfo e) override;

	virtual void AddRadioButtonStateSubscriber(RadioButtonStateSubscriber& subscriber) override;

	virtual void RemoveRadiobuttonStateSubscriber(RadioButtonStateSubscriber& subscriber) override;

};

