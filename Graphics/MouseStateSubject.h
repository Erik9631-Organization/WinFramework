#pragma once
class EventMouseStateInfo;
class MouseStateSubscriber;

class MouseStateSubject
{
public:
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) = 0;
	virtual void NotifyOnMouseUp(EventMouseStateInfo e) = 0;
	virtual void NotifyOnMousePressed(EventMouseStateInfo e) = 0;
	virtual void NotifyOnMouseHover(EventMouseStateInfo e) = 0;
	virtual void NotifyOnMouseEnter(EventMouseStateInfo e) = 0;
	virtual void NotifyOnMouseLeave(EventMouseStateInfo e) = 0;
	virtual void AddMouseStateSubscriber(MouseStateSubscriber& subscriber) = 0;
	virtual void RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber) = 0;
	virtual bool HasMouseEntered() = 0;
};

