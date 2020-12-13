#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "EventInfo.h"
class Component;

using namespace Gdiplus;
class EventMoveInfo : EventInfo
{
private:
	Point oldPosition;
public:
	Point GetRelativeOffset();
	Point GetPosition();
	EventMoveInfo(Point oldPosition, Component & component);
	~EventMoveInfo();
};

