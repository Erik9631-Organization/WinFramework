#include "EventMoveInfo.h"
#include "Component.h"

Point EventMoveInfo::GetRelativeOffset()
{
	Point newPosition = Point(component.GetPosition() - oldPosition);
	return newPosition;
}

Point EventMoveInfo::GetPosition()
{
	return component.GetPosition();
}

EventMoveInfo::EventMoveInfo(Point oldPosition, Component & component) : EventInfo(component)
{
	this->oldPosition = oldPosition;
}


EventMoveInfo::~EventMoveInfo()
{
}
