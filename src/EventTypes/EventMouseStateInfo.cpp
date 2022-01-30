#include "EventMouseStateInfo.h"
#include "Events/MouseStateSubject.h"
#include "Components/UiElement.h"

EventMouseStateInfo::EventMouseStateInfo(Vector2 position, int key, UiElement* src) : src(src)
{
	this->position = position;
	this->relativePosition = position - src->GetAbsolutePosition();
	this->key = key;
}

EventMouseStateInfo::EventMouseStateInfo(EventMouseStateInfo e, UiElement* source) : src(source)
{
	position = e.GetMouseAbsolutePosition();
	relativePosition = position - source->GetAbsolutePosition();
	recursive = e.recursive;
	key = e.GetKey();
	this->mouseDelta = e.GetMouseDelta();
}

EventMouseStateInfo::EventMouseStateInfo(EventMouseStateInfo e, Vector2 relativePosition, MouseStateSubject* src) : mouseSrc(src)
{
	this->position = e.GetMouseAbsolutePosition();
	this->relativePosition = relativePosition;
	this->key = e.GetKey();
	this->recursive = e.recursive;
	this->mouseDelta = e.GetMouseDelta();
}

Vector2 EventMouseStateInfo::GetMouseAbsolutePosition()
{
	return position;
}

Vector2 EventMouseStateInfo::GetMousePosition()
{
	if (src == nullptr)
		return GetMouseAbsolutePosition();
	return {GetMouseX(), GetMouseY()};
}

float EventMouseStateInfo::GetAbsoluteMouseX()
{
	return position.GetX();
}

float EventMouseStateInfo::GetAbsoluteMouseY()
{
	return position.GetY();
}

float EventMouseStateInfo::GetMouseX()
{
	if (src == nullptr && mouseSrc == nullptr)
		return GetAbsoluteMouseX();
	return relativePosition.GetX();
}

float EventMouseStateInfo::GetMouseY()
{
	if (src == nullptr && mouseSrc == nullptr)
		return GetAbsoluteMouseY();
	return relativePosition.GetY();
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

EventMouseStateInfo::EventMouseStateInfo(Vector2 position, Vector2 relativePosition, Vector2 delta,
                                         int key, MouseStateSubject *src)
{
    this->position = position;
    this->relativePosition = relativePosition;
    this->mouseDelta = delta;
    this->mouseSrc = src;
    this->key = key;
}

Vector2 EventMouseStateInfo::GetMouseDelta()
{
    return mouseDelta;
}
