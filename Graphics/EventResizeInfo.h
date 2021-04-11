#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "EventInfo.h"
#include <any>
#include "GenericObj.h"
class Resizable;

class EventResizeInfo
{
private:
	Gdiplus::Size size;
	Resizable* src;

public:
	Gdiplus::Size GetSize();
	Resizable* GetSrc();
	EventResizeInfo(Gdiplus::Size size, Resizable* src);
	~EventResizeInfo();
};

