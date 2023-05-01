#pragma once
#include "Events/MouseStateSubscriber.h"
#include <vector>
#include "Events/CheckboxStateSubject.h"
#include "glm.hpp"

class Checkbox;

class CheckBoxBehavior : public MouseStateSubscriber, public virtual CheckboxStateSubject
{
private:
	Checkbox& associatedCheckbox;
	glm::vec4 onClickColor = {150, 150, 150, 150};
	std::vector<std::reference_wrapper<CheckboxStateSubscriber>> subscribers;

public:
	CheckBoxBehavior(Checkbox& checkbox);

	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;

	virtual void OnMouseUp(EventMouseStateInfo e) override;

	virtual void OnMousePressed(EventMouseStateInfo e) override;

	virtual void OnMouseMove(EventMouseStateInfo e) override;

	virtual void OnMouseEntered(EventMouseStateInfo e) override;

	virtual void OnMouseLeft(EventMouseStateInfo e) override;


	// Inherited via CheckboxStateSubject
	virtual void AddCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber) override;

	virtual void RemoveCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber) override;

	virtual void NotifyOnChecked(EventCheckboxStateInfo info) override;

    void OnMouseCaptured(EventMouseStateInfo e) override;

};

