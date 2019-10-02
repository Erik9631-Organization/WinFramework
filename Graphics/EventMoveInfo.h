#pragma once
#include <Windows.h>
#include <gdiplus.h>
class Component;

using namespace Gdiplus;
class EventMoveInfo
{
private:
	Component & component;
	Point oldPosition;
public:
	Point GetRelativeOffset();
	Component & GetComponent();
	Point GetPosition();
	EventMoveInfo(Point oldPosition, Component & component);
	~EventMoveInfo();
};

