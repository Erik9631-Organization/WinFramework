#pragma once
class EventKeyStateInfo;
class KeyStateSubscriber;

class KeyStateSubject
{
	virtual void NotifyOnKeyDown(EventKeyStateInfo e) = 0;
	virtual void NotifyOnKeyUp(EventKeyStateInfo e) = 0;
	virtual void NotifyOnKeyPressed(EventKeyStateInfo e) = 0;
	virtual void AddKeyStateSubscriber(KeyStateSubscriber& subscriber) = 0;
	virtual void RemoveKeyStateSubscriber(KeyStateSubscriber& subscriber) = 0;
};

