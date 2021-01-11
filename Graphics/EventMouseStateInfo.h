#pragma once
#include <Windows.h>
#include <gdiplus.h>
class EventMouseStateInfo
{
	Gdiplus::Point position;
	int key;
	EventMouseStateInfo(Gdiplus::Point position, int key);
	Gdiplus::Point GetMousePosition();
	int GetMouseX();
	int GetMouseY();
	int GetKey();
};

