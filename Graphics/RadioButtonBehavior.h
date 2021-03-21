#pragma once
#include "MouseStateSubscriber.h"
#include <vector>
#include <memory>

class RadioButton;

class RadioButtonBehavior : MouseStateSubscriber
{
private:
	RadioButton& associatedRadioButton;
	std::shared_ptr<std::vector<std::reference_wrapper<RadioButton>>> group;
	void RemoveFromGroup(RadioButton& button);

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

};

