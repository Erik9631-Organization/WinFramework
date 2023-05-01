#pragma once
#include "EventSource.h"

class ActivateSubscriber;
class EventOnActivateInfo;

/**
 * This interface is implemented by all classes which can be observed for focus events.
 */
class ActivateSubject : public virtual EventSource
{
public:
	/**
	 * Adds a subscriber to the event stream
	 * \param subscriber the subscriber to be added
	 */
	virtual void AddOnActivateSubscriber(ActivateSubscriber& subscriber) = 0;

	/**
	 * Removes a subscriber from the event stream
	 * \param subscriber to be removed.
	 */
	virtual void RemoveOnActivateSubscriber(ActivateSubscriber& subscriber) = 0;

	/**
	 * Sends a focus which is propagated to all the subscribers.
	 * \param e event object to be sent.
	 */
	virtual void NotifyOnActivateStateChanged(EventOnActivateInfo& e) = 0;
};

