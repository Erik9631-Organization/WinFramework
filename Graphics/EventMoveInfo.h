#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "EventInfo.h"
class Component;

class EventMoveInfo
{
private:
	Gdiplus::Point position;
public:
	Gdiplus::Point GetPosition();
	EventMoveInfo(Gdiplus::Point position);
	~EventMoveInfo();
};

