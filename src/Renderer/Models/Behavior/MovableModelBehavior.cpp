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

float MovableModelBehavior::GetZ()
{
    return position.z;
}

float MovableModelBehavior::GetW()
{
    return position.w;
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
    auto prevPos = this->position;
    this->position = position;
    NotifyOnMoveSubscribers({position, prevPos, &owner});
}

void MovableModelBehavior::SetPosition(glm::vec4 position)
{
    SetPosition(position, true);
}

void MovableModelBehavior::SetPosition(float x, float y, float z, float w, bool emit)
{
    SetPosition({x, y, 0, 1}, emit);
}

///TODO: add Z and W to params
void MovableModelBehavior::SetPosition(float x, float y, float z, float w)
{
    SetPosition({x, y, 0, 1});
}

void MovableModelBehavior::SetX(float x, bool emit)
{
    SetPosition({x, position.x, position.z, position.w}, emit);
}

void MovableModelBehavior::SetX(float x)
{
    SetPosition({x, position.x, position.z, position.w});
}

void MovableModelBehavior::SetY(float y, bool emit)
{
    SetPosition({position.x, y, position.z, position.w}, emit);
}

void MovableModelBehavior::SetY(float y)
{
    SetPosition({position.x, y, position.z, position.w});
}

void MovableModelBehavior::SetZ(float z, bool emit)
{
    SetPosition({position.x, position.y, z, position.w}, emit);
}

void MovableModelBehavior::SetZ(float z)
{
    SetPosition({position.x, position.y, z, position.w});
}

void MovableModelBehavior::SetW(float w, bool emit)
{
    SetPosition({position.x, position.y, position.z, w}, emit);
}

void MovableModelBehavior::SetW(float w)
{
    SetPosition({position.x, position.y, position.z, w});
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

MovableModelBehavior::MovableModelBehavior(Movable &associatedMovable) : owner(associatedMovable)
{

}