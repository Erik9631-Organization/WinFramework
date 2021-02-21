#pragma once
#include <Windows.h>
#include <gdiplus.h>

class Component;
class EventMouseStateInfo
{
private:
	Gdiplus::Point position;
	Component* src;
	int key;
public:
	EventMouseStateInfo(Gdiplus::Point position, int key, Component* src);
	EventMouseStateInfo(EventMouseStateInfo e, Component* src);
	Gdiplus::Point GetMousePosition();
	int GetMouseX();
	int GetMouseY();
	int GetKey();
	Component* GetSrc();

};