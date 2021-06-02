#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "EventInfo.h"
#include <any>
#include "GenericObj.h"
class Resizable;
/**
 * This class is responsible for holding all the event information related to resizing
 */
class EventResizeInfo
{
private:
	Gdiplus::Size size;
	Resizable* src;

public:
	/**
	 * \return returns the size of the source at the point the event was called.
	 */
	Gdiplus::Size GetSize();

	/**
	 * \return returns source object that performed the call.
	 */
	Resizable* GetSrc();

	/**
	 * \param size the size of the source object
	 * \param src the source object that that called the event.
	 */
	EventResizeInfo(Gdiplus::Size size, Resizable* src);
	~EventResizeInfo();
};

