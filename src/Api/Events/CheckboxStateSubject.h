#pragma once
#include "EventSource.h"

class CheckboxStateSubscriber;
class EventCheckboxStateInfo;

class CheckboxStateSubject : public virtual EventSource
{
	virtual void AddCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber) = 0;
	virtual void RemoveCheckboxStateSubscriber(CheckboxStateSubscriber& subscriber) = 0;
	virtual void NotifyOnChecked(EventCheckboxStateInfo info) = 0;
};

