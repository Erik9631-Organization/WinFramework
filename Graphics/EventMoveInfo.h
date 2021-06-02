#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "EventInfo.h"
#include "GenericObj.h"

class Component;
class Movable;
/**
 * This class is responsible for holding event data related to movement.
 */
class EventMoveInfo
{
private:
	Gdiplus::Point position;
	Movable* src;
public:
	/**
	 * \return Returns the position of the source object at the point this event was called.
	 */
	Gdiplus::Point GetPosition();

	/**
	 * \return returns the source object that called the event.
	 */
	Movable* GetSrc();

	/**
	 * \param position the position of the source object.
	 * \param src the source object that called the event. 
	 */
	EventMoveInfo(Gdiplus::Point position, Movable* src);
	~EventMoveInfo();
};

