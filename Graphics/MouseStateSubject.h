#pragma once
class EventMouseStateInfo;
class MouseStateSubscriber;

class MouseStateSubject
{
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) = 0;
	virtual void NotifyOnMouseUp(EventMouseStateInfo e) = 0;
	virtual void NotifyOnMousePressed(EventMouseStateInfo e) = 0;
	virtual void NotifyOnMouseMove(EventMouseStateInfo e) = 0;
	virtual void AddMouseStateSubscriber(MouseStateSubscriber& subscriber) = 0;
	virtual void RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber) = 0;
};

