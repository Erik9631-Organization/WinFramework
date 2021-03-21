#pragma once
class CheckboxStateSubscriber;
class EventCheckboxStateInfo;

class CheckboxStateSubject
{
	virtual void AddCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber) = 0;
	virtual void RemoveCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber) = 0;
	virtual void NotifyOnChecked(EventCheckboxStateInfo info) = 0;
};

