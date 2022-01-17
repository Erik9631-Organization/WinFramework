#pragma once
#include "EventTypes/EventOnDragInfo.h"

class DragSubscriber;

/**
 * This interface is implemented by all the classes that can send drag events
 */
class DragSubject
{
public:
	/**
	 * Calls OnDragStart on all subscribers
	 * \param e the event object that contains all the drag data.
	 */
	virtual void NotifyOnDragStart(EventOnDragInfo e) = 0;

	/**
	* Calls OnDragEnd on all subscribers
	* \param e the event object that contains all the drag data.
	*/
	virtual void NotifyOnDragEnd(EventOnDragInfo e) = 0;

	/**
	 * \param subscriber Adds the subcriber to the drag even stream.
	*/
	virtual void AddOnDragSubscriber(DragSubscriber& subscriber) = 0;

	/**
	 * \param subscriber Removes the subcriber to the drag even stream.
	*/
	virtual void RemoveOnDragSubscriber(DragSubscriber& subscriber) = 0;
};

