//
// Created by Erik on 18/04/22.
//

#include "TickSubjectBehavior.h"


void TickSubjectBehavior::AddOnTickSubscriber(OnTickSubscriber *subscriber)
{
    subscribers.push_back(subscriber);
}

void TickSubjectBehavior::RemoveOnTickSubscriber(OnTickSubscriber *subscriber)
{
    for(auto it = subscribers.begin(); it < subscribers.end(); it++)
    {
        if(*it == subscriber)
        {
            subscribers.erase(it);
            return;
        }
    }
}

void TickSubjectBehavior::NotifyOnTick()
{
    for(auto* i : subscribers)
        i->OnTick();
}
