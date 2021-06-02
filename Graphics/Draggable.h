#pragma once
#include <any>
/**
 * An interface implemented by all the classes which are draggable.
 */
class Draggable
{
public:
	/**
	 * \return returns the object which was dragged.
	 */
	virtual std::any GetDragContent() = 0;
};

