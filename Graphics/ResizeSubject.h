#pragma once
class EventResizeInfo;
class ResizeSubscriber;
class ResizeSubject
{
public:
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) = 0;
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber ) = 0;
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber ) = 0;
};

