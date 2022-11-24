#include "EventMoveInfo.h"
#include "UiElement.h"
#include "api/Movable.h"


glm::vec2 EventMoveInfo::GetPosition() const
{
	return position;
}

Movable* EventMoveInfo::GetSrc() const
{
	return src;
}

EventMoveInfo::EventMoveInfo(glm::vec2 position, Movable* src) : src(src)
{
	this->position = position;
	this->src = src;
}


EventMoveInfo::~EventMoveInfo()
{
}
