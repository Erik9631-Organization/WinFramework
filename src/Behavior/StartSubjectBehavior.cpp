//
// Created by Erik on 18/04/22.
//

#include "StartSubjectBehavior.h"

void StartSubjectBehavior::AddOnStartSubscriber(StartSubscriber *subscriber)
{
    subscribers.push_back(subscriber);
}

void StartSubjectBehavior::RemoveOnStartSubscriber(StartSubscriber *subscriber)
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

void StartSubjectBehavior::NotifyOnStartSubscribers()
{
    for(auto* i : subscribers)
        i->OnStart();
}
