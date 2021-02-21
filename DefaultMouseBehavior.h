#pragma once
#include <vector>
#include "MouseStateSubject.h"
#include "MultiTree.h"
#include "MouseInteractable.h"
class Component;

class DefaultMouseBehavior : MouseStateSubject
{
private:
	std::vector<std::reference_wrapper<MouseStateSubscriber>> subscribers;
	MultiTree<MouseInteractable&>& associatedNode;
	bool mouseEntered = false;
public:
	DefaultMouseBehavior(MultiTree <MouseInteractable&> & node);
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

