#include "DefaultActivate.h"
#include "EventOnActivateInfo.h"
#include "ActivateSubscriber.h"

void DefaultActivate::AddOnActivateSubscriber(ActivateSubscriber& subscriber)
{
    subscribers.push_back(subscriber);
}

void DefaultActivate::RemoveOnActivateSubscriber(ActivateSubscriber& subscriber)
{
    for (std::vector<std::reference_wrapper<ActivateSubscriber>>::iterator i = subscribers.begin(); i != subscribers.end(); i++)
    {
        if (&i->get() == &subscriber)
        {
            subscribers.erase(i);
            return;
        }
    }
}


void DefaultActivate::SetActive(bool state)
{
    this->state = state;
    NotifyOnActivateStateChanged(EventOnActivateInfo(state));
    return;
}

bool DefaultActivate::IsActive()
{
    return state;
}

void DefaultActivate::NotifyOnActivateStateChanged(EventOnActivateInfo& activateInfo)
{
    for (ActivateSubscriber& subscriber : subscribers)
        subscriber.OnActiveStateChanged(activateInfo);
}
