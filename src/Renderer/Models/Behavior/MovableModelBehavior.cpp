//
// Created by erik9 on 12/12/2022.
//

#include "MovableModelBehavior.h"
#include "EventMoveInfo.h"

const glm::vec3 & MovableModelBehavior::GetPosition() const
{
    return position;
}

const glm::vec3 & MovableModelBehavior::GetAbsolutePosition() const
{
    return position;
}

void MovableModelBehavior::SetPosition(const glm::vec3 &position, bool emit)
{
    this->position = position;
    NotifyOnMoveSubscribers({position, GetAbsolutePosition(), &owner, false});
}

void MovableModelBehavior::SetTranslate(const glm::vec3 &offset, bool emit)
{
    translation = offset;
}

const glm::vec3 & MovableModelBehavior::GetTranslate() const
{
    return translation;
}

void MovableModelBehavior::AddOnMoveSubscriber(MoveSubscriber &subscriber)
{
    moveSubscribers.push_back(&subscriber);
}

void MovableModelBehavior::RemoveOnMoveSubscriber(MoveSubscriber &subscriber)
{
    for(auto it = moveSubscribers.begin(); it != moveSubscribers.end(); it++)
    {
        if(*it == &subscriber)
        {
            moveSubscribers.erase(it);
            return;
        }
    }
}

void MovableModelBehavior::NotifyOnMoveSubscribers(const EventMoveInfo &e)
{
    for(auto* subscriber : moveSubscribers)
        subscriber->OnMove(e);
}

MovableModelBehavior::MovableModelBehavior(Movable &associatedMovable) : owner(associatedMovable)
{

}