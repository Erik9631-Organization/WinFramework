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

EventMoveInfo::EventMoveInfo(const glm::vec4 &position, const glm::vec4 &absolutePosition,
                             const glm::vec4 &prevPosition,
                             const glm::vec4 &prevAbsolutePosition, Movable *src, bool isSource)
{
    this->position = position;
    this->prevPosition = prevPosition;
    this->prevAbsolutePosition = prevAbsolutePosition;
    this->absolutePosition = absolutePosition;
    this->src = src;
    this->isSource = isSource;
}

const glm::vec4 &EventMoveInfo::GetAbsolutePosition() const
{
    return absolutePosition;
}

bool EventMoveInfo::IsSource() const
{
    return isSource;
}
