#pragma once

#include "EventSource.h"

template<class T>
class OnAddSubscriber;

template<class T>
class EventOnAddInfo;

/**
 * This interface is implemented by all classes which are capable of sending OnAdd events.
 * \tparam type the type of object which can be added.
 */
template<class type>
class AddSubject : public virtual EventSource
{
	/**
	 * Sends an event when a new object is added to the containment hierarchy.
	 * \param e the event object to be sent.
	 */
	virtual void NotifyOnAddInfo(EventOnAddInfo<type> e) = 0;

	/**
	 * Adds a subscriber to to event stream.
	 * \param subscriber to be added.
	 */
	virtual void AddOnAddSubscriber(OnAddSubscriber<type>& subscriber) = 0;

	/**
	 * Removes a subscriber to to event stream.
	 * \param subscriber to be removed.
	 */
	virtual void RemoveOnAddSubscriber(OnAddSubscriber<type>& subscriber) = 0;
};

