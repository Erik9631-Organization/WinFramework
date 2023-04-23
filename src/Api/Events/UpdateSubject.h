#pragma once
class UpdateSubscriber;
class EventUpdateInfo;

class UpdateSubject
{
	virtual void AddOnUpdateSubscriber(UpdateSubscriber& subscriber) = 0;
	virtual void RemoveOnUpdateSubscriber(UpdateSubscriber& subscriber) = 0;
	virtual void NotifyOnUpdate(EventUpdateInfo& e) = 0;
};

