#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "EventInfo.h"
class Component;
class EventResizeInfo : EventInfo
{
public:
	Size oldSize;
	Gdiplus::Size GetSize();
	Gdiplus::Size GetRelativeSize();
	EventResizeInfo(Component & component);
	~EventResizeInfo();
};

