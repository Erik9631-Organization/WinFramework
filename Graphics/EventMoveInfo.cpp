#include "EventMoveInfo.h"
#include "Component.h"


Point EventMoveInfo::GetPosition()
{
	return position;
}

EventMoveInfo::EventMoveInfo(Point position)
{
	this->position = position;
}


EventMoveInfo::~EventMoveInfo()
{
}
