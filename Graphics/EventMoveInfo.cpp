#include "EventMoveInfo.h"
#include "Component.h"

Point EventMoveInfo::GetRelativeOffset()
{
	Point newPosition = Point(component.GetPosition() - oldPosition);
	return newPosition;
}

Component & EventMoveInfo::GetComponent()
{
	return component;
}

Point EventMoveInfo::GetPosition()
{
	return component.GetPosition();
}

EventMoveInfo::EventMoveInfo(Point oldPosition, Component & component) : component(component), oldPosition(oldPosition)
{
}


EventMoveInfo::~EventMoveInfo()
{
}
