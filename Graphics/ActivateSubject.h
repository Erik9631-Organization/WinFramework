#pragma once
class ActivateSubscriber;
class EventOnActivateInfo;

class ActivateSubject
{
public:
	virtual void AddOnActivateSubscriber(ActivateSubscriber& subscriber) = 0;
	virtual void RemoveOnActivateSubscriber(ActivateSubscriber& subscriber) = 0;
	virtual void NotifyOnActivateStateChanged(EventOnActivateInfo& activateInfo) = 0;
};

