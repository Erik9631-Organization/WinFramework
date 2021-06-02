#pragma once
#include "EventOnDragInfo.h"
class DropSubscriber;
/**
 * Interface implemented by all classes that can send drop events
 */
class DropSubject
{
public:

	/**
	 * Calls OnDrop on all subscribers
	 * \param e the event object that contains all the drag data.
	 */
	virtual void NotifyOnDrop(EventOnDragInfo e) = 0;

	/**
	 * \param subscriber Adds the subcriber to the drag even stream.
	*/
	virtual void AddOnDropSubscriber(DropSubscriber& subscriber) = 0;

	/**
	 * \param subscriber Removes the subcriber to the drag even stream.
	*/
	virtual void RemoveOnDropSubscriber(DropSubscriber& subscriber) = 0;
};

