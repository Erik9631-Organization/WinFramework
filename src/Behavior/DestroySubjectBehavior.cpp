//
// Created by Erik on 18/04/22.
//

#include "DestroySubjectBehavior.h"

void DestroySubjectBehavior::NotifyOnDestroy(DestroyEventInfo *e)
{
    for(auto* i : subscribers)
        i->OnObjectDestroyed(e);
}

void DestroySubjectBehavior::AddOnDestroySubscriber(DestroySubscriber *subscriber)
{
    subscribers.push_back(subscriber);
}

void DestroySubjectBehavior::RemoveOnDestroySubscriber(DestroySubscriber *subscriber)
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
