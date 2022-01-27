#include "EventMoveInfo.h"
#include "Components/UiElement.h"
#include "Components/Movable.h"


Point EventMoveInfo::GetPosition()
{
	return position;
}

Movable* EventMoveInfo::GetSrc()
{
	return src;
}

EventMoveInfo::EventMoveInfo(Point position, Movable* src) : src(src)
{
	this->position = position;
	this->src = src;
}


EventMoveInfo::~EventMoveInfo()
{
}
