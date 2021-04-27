#include "EventMouseStateInfo.h"
#include "MouseStateSubject.h"
#include "Component.h"

EventMouseStateInfo::EventMouseStateInfo(Gdiplus::Point position, Gdiplus::Point relativePosition, int key, MouseStateSubject* src) : mouseSrc(src)
{
	this->relativePosition = relativePosition;
	this->position = position;
	this->key = key;
}

EventMouseStateInfo::EventMouseStateInfo(Gdiplus::Point position, int key, Component* source) : src(source)
{
	this->position = position;
	this->relativePosition = position - source->GetAbsolutePosition();
	this->key = key;
}

EventMouseStateInfo::EventMouseStateInfo(EventMouseStateInfo e, Component* source) : src(source)
{
	position = e.GetMouseAbsolutePosition();
	relativePosition = position - source->GetAbsolutePosition();
	key = e.GetKey();
}

EventMouseStateInfo::EventMouseStateInfo(EventMouseStateInfo e, Gdiplus::Point relativePosition, MouseStateSubject* src) : mouseSrc(src)
{
	this->position = e.GetMouseAbsolutePosition();
	this->relativePosition = relativePosition;
	this->key = e.GetKey();
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
	if (src == nullptr && mouseSrc == nullptr)
		return GetAbsoluteMouseX();
	return relativePosition.X;
}

int EventMouseStateInfo::GetMouseY()
{
	if (src == nullptr && mouseSrc == nullptr)
		return GetAbsoluteMouseY();
	return relativePosition.Y;
}

int EventMouseStateInfo::GetKey()
{
	return key;
}

MouseStateSubject* EventMouseStateInfo::GetSrc()
{
	if (src == nullptr && mouseSrc == nullptr)
		return nullptr;

	if (src == nullptr)
		return mouseSrc;

	if(mouseSrc == nullptr)
		return src;
}
