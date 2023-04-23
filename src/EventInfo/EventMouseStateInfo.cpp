#include "EventMouseStateInfo.h"
#include "Events/MouseStateSubject.h"
#include "Components/UiElement.h"

EventMouseStateInfo::EventMouseStateInfo(glm::vec4 position, int key, UiElement* src) : src(src)
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

EventMouseStateInfo::EventMouseStateInfo(EventMouseStateInfo e, glm::vec4 relativePosition, MouseStateSubject* src) : mouseSrc(src)
{
	this->position = e.GetMouseAbsolutePosition();
	this->relativePosition = relativePosition;
	this->key = e.GetKey();
	this->recursive = e.recursive;
	this->mouseDelta = e.GetMouseDelta();
}

glm::vec4 EventMouseStateInfo::GetMouseAbsolutePosition()
{
	return position;
}

glm::vec4 EventMouseStateInfo::GetMousePosition()
{
	if (src == nullptr)
		return GetMouseAbsolutePosition();
	return {GetMouseX(), GetMouseY(), 0, 0};
}

float EventMouseStateInfo::GetAbsoluteMouseX()
{
	return position.x;
}

float EventMouseStateInfo::GetAbsoluteMouseY()
{
	return position.y;
}

float EventMouseStateInfo::GetMouseX()
{
	if (src == nullptr && mouseSrc == nullptr)
		return GetAbsoluteMouseX();
	return relativePosition.x;
}

float EventMouseStateInfo::GetMouseY()
{
	if (src == nullptr && mouseSrc == nullptr)
		return GetAbsoluteMouseY();
	return relativePosition.y;
}

int EventMouseStateInfo::GetKey()
{
	return key;
}

MouseStateSubject* EventMouseStateInfo::GetSrc()
{
	if (src == nullptr)
		return mouseSrc;

	if(mouseSrc == nullptr)
		return src;

    return nullptr;
}

void EventMouseStateInfo::SetRecursive(bool state)
{
	recursive = state;
}

bool EventMouseStateInfo::IsRecursive()
{
	return recursive;
}

EventMouseStateInfo::EventMouseStateInfo(glm::vec4 position, glm::vec4 relativePosition, glm::vec4 delta,
                                         int key, MouseStateSubject *src)
{
    this->position = position;
    this->relativePosition = relativePosition;
    this->mouseDelta = delta;
    this->mouseSrc = src;
    this->key = key;
}

glm::vec4 EventMouseStateInfo::GetMouseDelta()
{
    return mouseDelta;
}
