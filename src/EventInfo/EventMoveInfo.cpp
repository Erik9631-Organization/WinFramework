#include "EventMoveInfo.h"
#include "UiElement.h"
#include "api/Movable.h"


const glm::vec4 & EventMoveInfo::GetPosition() const
{
	return position;
}

Movable* EventMoveInfo::GetSrc() const
{
	return src;
}

EventMoveInfo::~EventMoveInfo()
{

}

EventMoveInfo::EventMoveInfo(const glm::vec4 &position, const glm::vec4 &absolutePosition, Movable *src, bool isOrigin)
{
    this->position = position;
    this->absolutePosition = absolutePosition;
    this->src = src;
    this->isOrigin = isOrigin;
}

const glm::vec4 &EventMoveInfo::GetAbsolutePosition() const
{
    return absolutePosition;
}

bool EventMoveInfo::IsOrigin() const
{
    return isOrigin;
}
