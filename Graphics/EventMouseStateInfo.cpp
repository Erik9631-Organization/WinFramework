#include "EventMouseStateInfo.h"
#include "Component.h"

EventMouseStateInfo::EventMouseStateInfo(Gdiplus::Point position, int key, Component* source) : src(source)
{
	this->position = position;
	this->key = key;
}

EventMouseStateInfo::EventMouseStateInfo(EventMouseStateInfo e, Component* source) : src(source)
{
	position = e.GetMousePosition();
	key = e.GetKey();
}

Gdiplus::Point EventMouseStateInfo::GetMousePosition()
{
	return position;
}

int EventMouseStateInfo::GetMouseX()
{
	return position.X;
}

int EventMouseStateInfo::GetMouseY()
{
	return position.Y;
}

int EventMouseStateInfo::GetKey()
{
	return key;
}

Component* EventMouseStateInfo::GetSrc()
{
	return src;
}
