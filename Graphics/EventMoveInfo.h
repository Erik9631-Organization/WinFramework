#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "EventInfo.h"
#include "GenericObj.h"

class Component;
class Movable;

class EventMoveInfo
{
private:
	Gdiplus::Point position;
	Movable* src;
public:
	Gdiplus::Point GetPosition();
	Movable* GetSrc();
	EventMoveInfo(Gdiplus::Point position, Movable* src);
	~EventMoveInfo();
};

