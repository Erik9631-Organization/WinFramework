#include "DefaultMouseBehavior.h"
#include "EventMouseStateInfo.h"
#include "MouseStateSubscriber.h"
#include "Component.h"

DefaultMouseBehavior::DefaultMouseBehavior(MultiTree<MouseInteractable&>& node) : associatedNode(node)
{

}

void DefaultMouseBehavior::NotifyOnMouseDown(EventMouseStateInfo e)
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

void DefaultMouseBehavior::NotifyOnMouseUp(EventMouseStateInfo e)
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

void DefaultMouseBehavior::NotifyOnMousePressed(EventMouseStateInfo e)
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

void DefaultMouseBehavior::NotifyOnMouseMove(EventMouseStateInfo e)
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
			if(associatedNode.Get(i).GetValue().HasMouseEntered())
				associatedNode.Get(i).GetValue().NotifyOnMouseLeave(e);
		}

	}
	if (subComponentCollision) // Notify only if there isn't another child at the point
		return;

	for (MouseStateSubscriber& subscriber : subscribers)
		subscriber.OnMouseMove(e);
}

void DefaultMouseBehavior::AddMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	subscribers.push_back(subscriber);
}

void DefaultMouseBehavior::RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber)
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

void DefaultMouseBehavior::NotifyOnMouseEnter(EventMouseStateInfo e)
{
	mouseEntered = true;
	for (MouseStateSubscriber& subscriber : subscribers)
		subscriber.OnMouseEntered(e);
}

void DefaultMouseBehavior::NotifyOnMouseLeave(EventMouseStateInfo e)
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

bool DefaultMouseBehavior::HasMouseEntered()
{
	return mouseEntered;
}
