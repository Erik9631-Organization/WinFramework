//
// Created by erik9 on 12/12/2022.
//

#include "MovableModelBehavior.h"
#include "EventMoveInfo.h"

glm::vec4 MovableModelBehavior::GetPosition()
{
    return position;
}

float MovableModelBehavior::GetX()
{
    return position.x;
}

float MovableModelBehavior::GetY()
{
    return position.y;
}

float MovableModelBehavior::GetAbsoluteX()
{
    return position.x;
}

float MovableModelBehavior::GetAbsoluteY()
{
    return position.y;
}

glm::vec4 MovableModelBehavior::GetAbsolutePosition()
{
    return position;
}

void MovableModelBehavior::SetPosition(glm::vec4 position, bool emit)
{
    this->position = position;
}

void MovableModelBehavior::SetPosition(glm::vec4 position)
{
    SetPosition(position, true);
}

void MovableModelBehavior::SetPosition(float x, float y, bool emit)
{
    SetPosition({x, y, 0, 0}, emit);
}

void MovableModelBehavior::SetPosition(float x, float y)
{
    SetPosition({x, y, 0, 0});
}

void MovableModelBehavior::SetX(float x, bool emit)
{
    SetPosition({x, position.x, 0, 0}, emit);
}

void MovableModelBehavior::SetX(float x)
{
    SetPosition({x, position.x, 0, 0});
}

void MovableModelBehavior::SetY(float y, bool emit)
{
    SetPosition({position.x, y, 0, 0}, emit);
}

void MovableModelBehavior::SetY(float y)
{
    SetPosition({position.x, y, 0, 0});
}

void MovableModelBehavior::SetTranslate(glm::vec4 offset, bool emit)
{
    translation = offset;
}

void MovableModelBehavior::SetTranslate(glm::vec4 offset)
{
    translation = offset;
}

void MovableModelBehavior::SetTranslateX(float x, bool emit)
{
    translation.x = x;
}

void MovableModelBehavior::SetTranslateX(float x)
{
    translation.x = x;
}

void MovableModelBehavior::SetTranslateY(float y, bool emit)
{
    translation.y = y;
}

void MovableModelBehavior::SetTranslateY(float y)
{
    translation.y = y;
}

glm::vec4 MovableModelBehavior::GetTranslate()
{
    return translation;
}

float MovableModelBehavior::GetTranslateX()
{
    return translation.x;
}

float MovableModelBehavior::GetTranslateY()
{
    return translation.y;
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

void MovableModelBehavior::NotifyOnMoveSubscribers(EventMoveInfo e)
{
    for(auto* subscriber : moveSubscribers)
        subscriber->OnMove(e);
}
