#pragma once
#include "EventSource.h"
class MoveSubscriber;
class EventMoveInfo;

/**
 * This interface is implemented by all classes which are capable of sending OnMove events
 */
class MoveSubject : public virtual EventSource
{
public:
	/**
	 * Adds a new subscriber to the event stream.
	 * \param subscriber to be added to the event stream.
	 */
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) = 0;

	/**
	 * Removes a subscriber from the event stream.
	 * \param the subscriber to be removed from the event stream.
	 */
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) = 0;

	/**
	 * Sends an event to all the subscribers of this object.
	 * \param e the event object that should be sent to the subscribers.
	 */
	virtual void NotifyOnMoveSubscribers(const EventMoveInfo &e) = 0;
};

