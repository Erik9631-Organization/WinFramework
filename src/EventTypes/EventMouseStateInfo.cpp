#include "EventMouseStateInfo.h"
#include "Events/MouseStateSubject.h"
#include "Components/Component.h"

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
	recursive = e.recursive;
	key = e.GetKey();
	this->mouseDelta = e.GetMouseDelta();
}

EventMouseStateInfo::EventMouseStateInfo(EventMouseStateInfo e, Gdiplus::Point relativePosition, MouseStateSubject* src) : mouseSrc(src)
{
	this->position = e.GetMouseAbsolutePosition();
	this->relativePosition = relativePosition;
	this->key = e.GetKey();
	this->recursive = e.recursive;
	this->mouseDelta = e.GetMouseDelta();
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

void EventMouseStateInfo::SetRecursive(bool state)
{
	recursive = state;
}

bool EventMouseStateInfo::IsRecursive()
{
	return recursive;
}

EventMouseStateInfo::EventMouseStateInfo(Gdiplus::Point position, Gdiplus::Point relativePosition, Gdiplus::Point delta,
                                         int key, MouseStateSubject *src)
{
    this->position = position;
    this->relativePosition = relativePosition;
    this->mouseDelta = delta;
    this->mouseSrc = src;
    this->key = key;
}

Gdiplus::Point EventMouseStateInfo::GetMouseDelta()
{
    return mouseDelta;
}
