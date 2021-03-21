#pragma once
#include <vector>
#include "MouseStateSubject.h"
#include "MouseInteractable.h"
#include "DefaultMouseBehavior.h"
#include "EventMouseStateInfo.h"
#include "MouseStateSubscriber.h"

template<class TreeNode>
class DefaultMouseBehavior : public MouseStateSubject
{
private:
	std::vector<std::reference_wrapper<MouseStateSubscriber>> subscribers;
	TreeNode associatedNode;
	bool mouseEntered = false;
public:
	DefaultMouseBehavior(TreeNode node);
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

template<class TreeNode>
DefaultMouseBehavior<TreeNode>::DefaultMouseBehavior(TreeNode node) : associatedNode(node)
{

}

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMouseDown(EventMouseStateInfo e)
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

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMouseUp(EventMouseStateInfo e)
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

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMousePressed(EventMouseStateInfo e)
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

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::NotifyOnMouseMove(EventMouseStateInfo e)
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


template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::AddMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	subscribers.push_back(subscriber);
}

template<class TreeNode>
void DefaultMouseBehavior<TreeNode>::RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber)
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
