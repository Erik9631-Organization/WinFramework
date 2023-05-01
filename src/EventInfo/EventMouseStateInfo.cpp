#include "EventMouseStateInfo.h"
#include "Events/MouseStateSubject.h"
#include "Components/UiElement.h"
//TODO change to references
EventMouseStateInfo::EventMouseStateInfo(EventMouseStateInfo e, glm::vec3 relativePosition, EventSource *src)
{
	this->position = e.GetMouseAbsolutePosition();
	this->relativePosition = relativePosition;
	this->key = e.GetKey();
	this->recursive = e.recursive;
	this->mouseDelta = e.GetMouseDelta();
}

glm::vec3 EventMouseStateInfo::GetMouseAbsolutePosition()
{
	return position;
}

glm::vec3 EventMouseStateInfo::GetMousePosition()
{
	if (src == nullptr)
		return GetMouseAbsolutePosition();
	return {GetMouseX(), GetMouseY(), 0};
}

float EventMouseStateInfo::GetAbsoluteMouseX() const
{
	return position.x;
}

float EventMouseStateInfo::GetAbsoluteMouseY() const
{
	return position.y;
}

float EventMouseStateInfo::GetMouseX()
{
	if (src == nullptr)
		return GetAbsoluteMouseX();
	return relativePosition.x;
}

float EventMouseStateInfo::GetMouseY()
{
	if (src == nullptr)
		return GetAbsoluteMouseY();
	return relativePosition.y;
}

int EventMouseStateInfo::GetKey()
{
	return key;
}

void EventMouseStateInfo::SetRecursive(bool state)
{
	recursive = state;
}

bool EventMouseStateInfo::IsRecursive()
{
	return recursive;
}

EventMouseStateInfo::EventMouseStateInfo(glm::vec3 position, glm::vec3 relativePosition, glm::vec3 delta,
                                         int key, EventSource *src)
{
    this->position = position;
    this->relativePosition = relativePosition;
    this->mouseDelta = delta;
    this->src = src;
    this->key = key;
}

glm::vec3 EventMouseStateInfo::GetMouseDelta()
{
    return mouseDelta;
}

EventSource *EventMouseStateInfo::GetSource() const
{
    return src;
}
