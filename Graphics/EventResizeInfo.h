#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "EventInfo.h"
class EventResizeInfo
{
private:
	Gdiplus::Size size;
public:
	Gdiplus::Size GetSize();
	EventResizeInfo(Gdiplus::Size size);
	~EventResizeInfo();
};

