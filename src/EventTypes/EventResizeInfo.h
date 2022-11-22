#pragma once
#include "EventInfo.h"
#include <any>
#include <Vector2.h>
#include "GenericObj.h"
class Resizable;
/**
 * This class is responsible for holding all the event information related to resizing
 */
class EventResizeInfo
{
private:
	Vector2 size;
	Resizable* src;

public:
	/**
	 * \return returns the size of the source at the point the event was called.
	 */
    Vector2 GetSize() const;

	/**
	 * \return returns source object that performed the call.
	 */
	Resizable* GetSrc() const;

	/**
	 * \param size the size of the source object
	 * \param src the source object that that called the event.
	 */
	EventResizeInfo(Vector2 size, Resizable* src);
	~EventResizeInfo();
};

