#include "DefaultActivate.h"
#include "EventOnActivateInfo.h"
#include "ActivateSubscriber.h"

void DefaultActivate::SetActivatable(bool state)
{
    activatable = state;
}

bool DefaultActivate::IsActivatable()
{
    return activatable;
}

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
    auto event{EventOnActivateInfo(state, this)};
    NotifyOnActivateStateChanged(event);
}

bool DefaultActivate::IsActive()
{
    if (!activatable)
        return false;

    return state;
}

void DefaultActivate::NotifyOnActivateStateChanged(EventOnActivateInfo& activateInfo)
{
    for (ActivateSubscriber& subscriber : subscribers)
        subscriber.OnActiveStateChanged(activateInfo);
}
