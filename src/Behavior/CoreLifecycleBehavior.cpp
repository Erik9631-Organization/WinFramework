//
// Created by erik9 on 5/14/2023.
//

#include "CoreLifecycleBehavior.h"
#include "Core.h"

void CoreLifecycleBehavior::NotifyOnCoreInit(const EventCoreLifecycleInfo &e)
{
    for (auto &subscriber : subscribers)
        subscriber->OnCoreInit(e);
    if(currentState < State::INIT)
        currentState = State::INIT;
}

void CoreLifecycleBehavior::NotifyOnCoreStart(const EventCoreLifecycleInfo &e)
{
    for (auto &subscriber : subscribers)
        subscriber->OnCoreStart(e);
    if(currentState < State::START)
        currentState = State::START;
}

void CoreLifecycleBehavior::NotifyOnCoreStop(const EventCoreLifecycleInfo &e)
{
    for (auto &subscriber : subscribers)
        subscriber->OnCoreStop(e);
    if(currentState < State::STOP)
        currentState = State::STOP;
}

void CoreLifecycleBehavior::NotifyOnCoreDestroy(const EventCoreLifecycleInfo &e)
{
    for (auto &subscriber : subscribers)
        subscriber->OnCoreDestroy(e);
    if(currentState < State::DESTROY)
        currentState = State::DESTROY;
}

void CoreLifecycleBehavior::AddCoreLifecycleSubscriber(CoreLifecycleSubscriber *subscriber)
{
    NotifyNewSubscriber(subscriber);
    subscribers.push_back(subscriber);
}

void CoreLifecycleBehavior::RemoveCoreLifecycleSubscriber(CoreLifecycleSubscriber *subscriber)
{
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
}

void CoreLifecycleBehavior::NotifyNewSubscriber(CoreLifecycleSubscriber *subscriber)
{
    switch (currentState)
    {
        case State::INIT:
            subscriber->OnCoreInit(EventCoreLifecycleInfo(&associatedCore, &associatedCore));
            break;
        case State::START:
            subscriber->OnCoreInit(EventCoreLifecycleInfo(&associatedCore, &associatedCore));
            subscriber->OnCoreStart(EventCoreLifecycleInfo(&associatedCore, &associatedCore));
            break;
        case State::STOP:
            subscriber->OnCoreStop(EventCoreLifecycleInfo(&associatedCore, &associatedCore));
            break;
        case State::DESTROY:
            subscriber->OnCoreDestroy(EventCoreLifecycleInfo(&associatedCore, &associatedCore));
            break;
        default:
            break;
    }
}

CoreLifecycleBehavior::CoreLifecycleBehavior(Core &associatedCore) :
    associatedCore(associatedCore)
{

}
