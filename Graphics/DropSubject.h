#pragma once
#include "EventOnDragInfo.h"
class DropSubscriber;

class DropSubject
{
public:
	virtual void NotifyOnDrop(EventOnDragInfo e) = 0;
	virtual void AddOnDropSubscriber(DropSubscriber& subscriber) = 0;
	virtual void RemoveOnDropSubscriber(DropSubscriber& subscriber) = 0;
};

