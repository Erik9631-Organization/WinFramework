#pragma once
#include <vector>
#include "MouseStateSubject.h"
#include "MouseInteractable.h"
#include "DefaultMouseBehavior.h"
#include "EventMouseStateInfo.h"
#include "MouseStateSubscriber.h"

template<class T>
class DefaultMouseBehavior : public MouseStateSubject
{
private:
	std::vector<std::reference_wrapper<MouseStateSubscriber>> subscribers;
	T associatedNode;
	bool mouseEntered = false;
public:
	DefaultMouseBehavior(T node);
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseUp(EventMouseStateInfo e) override;
	virtual void NotifyOnMousePressed(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseMove(EventMouseStateInfo e) override;
	virtual void AddMouseStateSubscriber(MouseStateSubscriber& subscriber) override;
	virtual void RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber) override;
	virtual void NotifyOnMouseEnter(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseLeave(EventMouseStateInfo e) override;
	virtual bool HasMouseEntered() override;
};

template<class T>
DefaultMouseBehavior<T>::DefaultMouseBehavior(T node) : associatedNode(node)
{

}

template<class T>
void DefaultMouseBehavior<T>::NotifyOnMouseDown(EventMouseStateInfo e)
{
	bool subComponentCollision = false;
	for (int i = 0; i < associatedNode.GetNodeCount(); i++) // Should also notify subNodes
	{
		if (associatedNode.Get(i).GetValue().ColidesWithPoint(e.GetMousePosition()))
		{
			associatedNode.Get(i).GetValue().NotifyOnMouseDown(e);
			subComponentCollision = true;
		}
	}
	if (subComponentCollision) // Notify only if there isn't another child at the point
		return;

	for (MouseStateSubscriber& subscriber : subscribers)
		subscriber.OnMouseDown(e);
}

template<class T>
void DefaultMouseBehavior<T>::NotifyOnMouseUp(EventMouseStateInfo e)
{
	bool subComponentCollision = false;
	for (int i = 0; i < associatedNode.GetNodeCount(); i++) // Should also notify subNodes
	{
		if (associatedNode.Get(i).GetValue().ColidesWithPoint(e.GetMousePosition()))
		{
			associatedNode.Get(i).GetValue().NotifyOnMouseUp(e);
			subComponentCollision = true;
		}
	}
	if (subComponentCollision) // Notify only if there isn't another child at the point
		return;

	for (MouseStateSubscriber& subscriber : subscribers)
		subscriber.OnMouseUp(e);
}

template<class T>
void DefaultMouseBehavior<T>::NotifyOnMousePressed(EventMouseStateInfo e)
{
	bool subComponentCollision = false;
	for (int i = 0; i < associatedNode.GetNodeCount(); i++) // Should also notify subNodes
	{
		if (associatedNode.Get(i).GetValue().ColidesWithPoint(e.GetMousePosition()))
		{
			associatedNode.Get(i).GetValue().NotifyOnMousePressed(e);
			subComponentCollision = true;
		}
	}
	if (subComponentCollision) // Notify only if there isn't another child at the point
		return;

	for (MouseStateSubscriber& subscriber : subscribers)
		subscriber.OnMousePressed(e);
}

template<class T>
void DefaultMouseBehavior<T>::NotifyOnMouseMove(EventMouseStateInfo e)
{
	if (!mouseEntered)
		NotifyOnMouseEnter(e);

	bool subComponentCollision = false;
	for (int i = 0; i < associatedNode.GetNodeCount(); i++) // Should also notify subNodes
	{
		if (associatedNode.Get(i).GetValue().ColidesWithPoint(e.GetMousePosition()))
		{
			associatedNode.Get(i).GetValue().NotifyOnMouseMove(e);
			subComponentCollision = true;
		}
		else
		{
			if (associatedNode.Get(i).GetValue().HasMouseEntered())
				associatedNode.Get(i).GetValue().NotifyOnMouseLeave(e);
		}

	}
	if (subComponentCollision) // Notify only if there isn't another child at the point
		return;

	for (MouseStateSubscriber& subscriber : subscribers)
		subscriber.OnMouseMove(e);
}


template<class T>
void DefaultMouseBehavior<T>::AddMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	subscribers.push_back(subscriber);
}

template<class T>
void DefaultMouseBehavior<T>::RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	for (std::vector<std::reference_wrapper<MouseStateSubscriber>>::iterator i = subscribers.begin(); i != subscribers.end(); i++)
	{
		if (&i->get() == &subscriber)
		{
			subscribers.erase(i);
			return;
		}
	}
}

template<class T>
void DefaultMouseBehavior<T>::NotifyOnMouseEnter(EventMouseStateInfo e)
{
	mouseEntered = true;
	for (MouseStateSubscriber& subscriber : subscribers)
		subscriber.OnMouseEntered(e);
}

template<class T>
void DefaultMouseBehavior<T>::NotifyOnMouseLeave(EventMouseStateInfo e)
{
	for (int i = 0; i < associatedNode.GetNodeCount(); i++) // Check if left from any of the subcomponents
	{
		if (associatedNode.Get(i).GetValue().HasMouseEntered())
			associatedNode.Get(i).GetValue().NotifyOnMouseLeave(e);
	}

	mouseEntered = false;
	for (MouseStateSubscriber& subscriber : subscribers)
		subscriber.OnMouseLeft(e);
}

template<class T>
bool DefaultMouseBehavior<T>::HasMouseEntered()
{
	return mouseEntered;
}
