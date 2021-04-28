#pragma once
#include "ResizeSubscriber.h"
#include "MouseStateSubscriber.h"
#include "ActivateSubscriber.h"
#include "ComboBoxStateSubscriber.h"
#include "ComboBoxStateSubject.h"
#include <vector>

class ComboBox;
class Button;
class ComboSelection;

class DefaultComboBoxBehavior : public ResizeSubscriber, public MouseStateSubscriber, public ActivateSubscriber, public ComboBoxStateSubscriber, public ComboBoxStateSubject
{
private:
	ComboBox& associatedComboBox;
	ComboSelection& associatedComboSelection;
	Button* comboBoxButton = nullptr;
	std::vector<std::reference_wrapper<ComboBoxStateSubscriber>> subscribers;

public:
	DefaultComboBoxBehavior(ComboBox& associatedComboBox, Button* comboBoxButton, ComboSelection& selection);

	// Inherited via ResizeSubscriber
	virtual void OnResize(EventResizeInfo e) override;


	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;

	virtual void OnMouseUp(EventMouseStateInfo e) override;

	virtual void OnMousePressed(EventMouseStateInfo e) override;

	virtual void OnMouseMove(EventMouseStateInfo e) override;

	virtual void OnMouseEntered(EventMouseStateInfo e) override;

	virtual void OnMouseLeft(EventMouseStateInfo e) override;


	// Inherited via ActivateSubscriber
	virtual void OnActiveStateChanged(EventOnActivateInfo) override;


	// Inherited via ComboBoxStateSubscriber
	virtual void OnComboBoxOpened(EventComboBoxStateInfo e) override;

	virtual void OnComboBoxClosed(EventComboBoxStateInfo e) override;

	virtual void OnSelectionChanged(EventComboBoxStateInfo e) override;


	// Inherited via ComboBoxStateSubject
	virtual void NotifyOnComboBoxOpened(EventComboBoxStateInfo e) override;

	virtual void NotifyOnComboBoxClosed(EventComboBoxStateInfo e) override;

	virtual void NotifyOnSelectionChanged(EventComboBoxStateInfo e) override;

	virtual void AddComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber) override;

	virtual void RemoveComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber) override;

};

