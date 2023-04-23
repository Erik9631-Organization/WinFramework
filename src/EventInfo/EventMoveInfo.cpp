#include "EventMoveInfo.h"
#include "UiElement.h"
#include "api/Movable.h"


glm::vec4 EventMoveInfo::GetPosition() const
{
	return position;
}

Movable* EventMoveInfo::GetSrc() const
{
	return src;
}

EventMoveInfo::EventMoveInfo(glm::vec4 position, Movable* src) : src(src)
{
	this->position = position;
	this->src = src;
}

EventMoveInfo::~EventMoveInfo()
{
}

EventMoveInfo::EventMoveInfo(glm::vec4 position, glm::vec4 prevPosition, Movable *src)
{
    this->position = position;
    this->prevPosition = prevPosition;
    this->src = src;
}

const glm::vec4 &EventMoveInfo::GetPrevPosition() const
{
    return prevPosition;
}
