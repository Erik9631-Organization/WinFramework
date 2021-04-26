#include "EventMouseStateInfo.h"
#include "MouseStateSubject.h"
#include "Component.h"

EventMouseStateInfo::EventMouseStateInfo(Gdiplus::Point position, int key, Component* source) : src(source)
{
	this->position = position;
	this->key = key;
}

EventMouseStateInfo::EventMouseStateInfo(EventMouseStateInfo e, Component* source) : src(source)
{
	position = e.GetMouseAbsolutePosition();
	key = e.GetKey();
}

Gdiplus::Point EventMouseStateInfo::GetMouseAbsolutePosition()
{
	return position;
}

Gdiplus::Point EventMouseStateInfo::GetMousePosition()
{
	if (src == nullptr)
		return GetMouseAbsolutePosition();
	return Point(GetMouseX(), GetMouseY());
}

int EventMouseStateInfo::GetAbsoluteMouseX()
{
	return position.X;
}

int EventMouseStateInfo::GetAbsoluteMouseY()
{
	return position.Y;
}

int EventMouseStateInfo::GetMouseX()
{
	if (src == nullptr)
		return GetAbsoluteMouseX();
	return position.X - src->GetAbsoluteX();
}

int EventMouseStateInfo::GetMouseY()
{
	if (src == nullptr)
		return GetAbsoluteMouseY();

	return  position.Y - src->GetAbsoluteY();
}

int EventMouseStateInfo::GetKey()
{
	return key;
}

MouseStateSubject* EventMouseStateInfo::GetSrc()
{
	return src;
}
