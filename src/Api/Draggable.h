#pragma once
#include <any>
#include "EventSource.h"

/**
 * An interface implemented by all the classes which are draggable.
 */
class Draggable : public virtual EventSource
{
public:
	/**
	 * \return returns the object which was dragged.
	 */
	virtual std::any GetDragContent() = 0;
};

