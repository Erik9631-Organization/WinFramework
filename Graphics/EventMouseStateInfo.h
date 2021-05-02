#pragma once
#include <Windows.h>
#include <gdiplus.h>

class Component;
class MouseStateSubject;
class EventMouseStateInfo
{
private:
	Gdiplus::Point position;
	Gdiplus::Point relativePosition;
	Component* src = nullptr; // Kept here for compatibility reasons
	MouseStateSubject* mouseSrc = nullptr; // Alternative source parameter
	bool recursive = true; // Notifies the topmost component on the position if there is any, if set to false, then only notifies the target
	int key;
public:
	EventMouseStateInfo(Gdiplus::Point position, Gdiplus::Point relativePosition, int key, MouseStateSubject* src);
	EventMouseStateInfo(Gdiplus::Point position, int key, Component* src);

	EventMouseStateInfo(EventMouseStateInfo e, Component* src);
	EventMouseStateInfo(EventMouseStateInfo e, Gdiplus::Point relativePosition, MouseStateSubject* src);
	Gdiplus::Point GetMouseAbsolutePosition();
	Gdiplus::Point GetMousePosition();

	int GetAbsoluteMouseX();
	int GetAbsoluteMouseY();
	int GetMouseX();
	int GetMouseY();
	int GetKey();
	MouseStateSubject* GetSrc();
	void SetRecursive(bool state);
	bool IsRecursive();

};