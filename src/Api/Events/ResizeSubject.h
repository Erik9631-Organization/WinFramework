#pragma once
#include "EventSource.h"
class EventResizeInfo;
class ResizeSubscriber;
/**
 * An interface for all classes which are resizable. If the interface is implemented, it will automatically become an observable subject.
 * The class implementing this interface should also implement an array where it can contain and notify its subscribers when ResizeSubject::NotifyOnResizeSubscribers is called.
 */
class ResizeSubject : public virtual EventSource
{
public:
	/**
	 * Called if an event is passed to all the subscribers/observers.
	 * \param event the object containing event specific information
	 */
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) = 0;
	/**
	 * Used to add a new subscriber to the event stream
	 * \param subscriber a reference to the subscriber that wants to be added.
	 */
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber ) = 0;

	/**
	 * Used to remove a subscriber from the event stream
	 * \param subscriber a reference to the subscriber that wants to be removed.
	 */
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber ) = 0;
};

