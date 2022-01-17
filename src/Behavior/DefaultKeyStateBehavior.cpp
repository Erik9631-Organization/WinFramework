#include "DefaultKeyStateBehavior.h"
#include "EventTypes/EventKeyStateInfo.h"

DefaultKeyStateBehavior::DefaultKeyStateBehavior(Activatable& activatable) : associatedActivatable(activatable)
{

}

void DefaultKeyStateBehavior::NotifyOnKeyDown(EventKeyStateInfo e)
{
	if (!associatedActivatable.IsActive())
		return;
	for (KeyStateSubscriber& subscriber : subscribers)
		subscriber.OnKeyDown(e);
}

void DefaultKeyStateBehavior::NotifyOnKeyUp(EventKeyStateInfo e)
{
	if (!associatedActivatable.IsActive())
		return;
	for (KeyStateSubscriber& subscriber : subscribers)
		subscriber.OnKeyUp(e);
}

void DefaultKeyStateBehavior::NotifyOnKeyPressed(EventKeyStateInfo e)
{
	if (!associatedActivatable.IsActive())
		return;
	for (KeyStateSubscriber& subscriber : subscribers)
		subscriber.OnKeyPressed(e);
}

void DefaultKeyStateBehavior::AddKeyStateSubscriber(KeyStateSubscriber& subscriber)
{
	subscribers.push_back(subscriber);
}

void DefaultKeyStateBehavior::RemoveKeyStateSubscriber(KeyStateSubscriber& subscriber)
{
	for (std::vector<std::reference_wrapper<KeyStateSubscriber>>::iterator it = subscribers.begin(); it != subscribers.end(); it++)
		if (&(*it).get() == &subscriber)
			subscribers.erase(it);
}
