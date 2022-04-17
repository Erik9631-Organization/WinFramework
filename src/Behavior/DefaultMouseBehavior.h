#pragma once
#include <vector>
#include "Events/MouseStateSubject.h"
#include "api/MouseInteractable.h"
#include "DefaultMouseBehavior.h"
#include "EventTypes/EventMouseStateInfo.h"
#include "Events/MouseStateSubscriber.h"

template<class TreeNode>
class DefaultMouseBehavior : public MouseStateSubject
{
private:
	std::vector<std::reference_wrapper<MouseStateSubscriber>> subscribers;
	TreeNode associatedNode;
	bool mouseEntered = false;
	bool mouseCaptured = false;
public:
	DefaultMouseBehavior(TreeNode node);
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseUp(EventMouseStateInfo e) override;
	virtual void NotifyOnMousePressed(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseHover(EventMouseStateInfo e) override;
	virtual void AddMouseStateSubscriber(MouseStateSubscriber& subscriber) override;
	virtual void RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber) override;
	virtual void NotifyOnMouseEnter(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseLeave(EventMouseStateInfo e) override;
	virtual bool HasMouseEntered() override;
    void NotifyOnMouseCapture(EventMouseStateInfo e) override;
    bool IsMouseCaptured() override;
    void SetMouseCaptured(bool state) override;
};

template<class TreeNode>
DefaultMouseBehavior<TreeNode>::DefaultMouseBehavior(TreeNode node) : associatedNode(node)
{

}

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMouseDown(EventMouseStateInfo e)
{

	if (!e.IsRecursive())
	{
		for (MouseStateSubscriber& subscriber : subscribers)
			subscriber.OnMouseDown(e);
		return;
	}

	bool subComponentCollision = false;
	for (int i = 0; i < associatedNode.GetNodeCount(); i++) // Should also notify subNodes
	{
		if (associatedNode.Get(i).GetValue().ColidesWithPoint(e.GetMouseAbsolutePosition()))
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

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMouseUp(EventMouseStateInfo e)
{
    mouseCaptured = false;
	if (!e.IsRecursive())
	{
		for (MouseStateSubscriber& subscriber : subscribers)
			subscriber.OnMouseUp(e);
		return;
	}


	bool subComponentCollision = false;
	for (int i = 0; i < associatedNode.GetNodeCount(); i++) // Should also notify subNodes
	{
		if (associatedNode.Get(i).GetValue().ColidesWithPoint(e.GetMouseAbsolutePosition()))
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

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMousePressed(EventMouseStateInfo e)
{
	if (!e.IsRecursive())
	{
		for (MouseStateSubscriber& subscriber : subscribers)
			subscriber.OnMousePressed(e);
		return;
	}




	bool subComponentCollision = false;
	for (int i = 0; i < associatedNode.GetNodeCount(); i++) // Should also notify subNodes
	{
		if (associatedNode.Get(i).GetValue().ColidesWithPoint(e.GetMouseAbsolutePosition()))
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

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMouseHover(EventMouseStateInfo e)
{
	if (!mouseEntered)
		NotifyOnMouseEnter(e);

	if (!e.IsRecursive())
	{
		for (MouseStateSubscriber& subscriber : subscribers)
			subscriber.OnMouseMove(e);
		return;
	}


	bool subComponentCollision = false;
	for (int i = 0; i < associatedNode.GetNodeCount(); i++) // Should also notify subNodes
	{
		if (associatedNode.Get(i).GetValue().ColidesWithPoint(e.GetMouseAbsolutePosition()))
		{
			associatedNode.Get(i).GetValue().NotifyOnMouseHover(e);
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


template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::AddMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	subscribers.push_back(subscriber);
}

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	for (auto i = subscribers.begin(); i != subscribers.end(); i++)
	{
		if (&i->get() == &subscriber)
		{
			subscribers.erase(i);
			return;
		}
	}
}

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMouseEnter(EventMouseStateInfo e)
{
	mouseEntered = true;
	for (MouseStateSubscriber& subscriber : subscribers)
		subscriber.OnMouseEntered(e);
}

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMouseLeave(EventMouseStateInfo e)
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

template<class TreeNode>
bool DefaultMouseBehavior<TreeNode>::HasMouseEntered()
{
	return mouseEntered;
}

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMouseCapture(EventMouseStateInfo e)
{
    mouseCaptured = true;
    for(MouseStateSubscriber& subscriber : subscribers)
        subscriber.OnMouseCaptured(e);

}

template<class TreeNode>
bool DefaultMouseBehavior<TreeNode>::IsMouseCaptured()
{
    return mouseCaptured;
}

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::SetMouseCaptured(bool state)
{
    mouseCaptured = state;
}
