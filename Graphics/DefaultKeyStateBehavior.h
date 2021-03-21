#pragma once
#include "KeyStateSubject.h"
#include "KeyStateSubscriber.h"
#include <vector>
#include "InputManager.h"
#include "Activatable.h"
class DefaultKeyStateBehavior : KeyStateSubject
{
private:
	std::vector<std::reference_wrapper<KeyStateSubscriber>> subscribers;
	InputManager manager;
	Activatable& associatedActivatable;
public:
	DefaultKeyStateBehavior(Activatable& activatable);

	// Inherited via KeyStateSubject
	virtual void NotifyOnKeyDown(EventKeyStateInfo e) override;
	virtual void NotifyOnKeyUp(EventKeyStateInfo e) override;
	virtual void NotifyOnKeyPressed(EventKeyStateInfo e) override;
	virtual void AddKeyStateSubscriber(KeyStateSubscriber& subscriber) override;
	virtual void RemoveKeyStateSubscriber(KeyStateSubscriber& subscriber) override;
};

