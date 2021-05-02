#pragma once
#include "EventOnDragInfo.h"

class DragSubscriber;
class DragSubject
{
public:
	virtual void NotifyOnDragStart(EventOnDragInfo e) = 0;
	virtual void NotifyOnDragEnd(EventOnDragInfo e) = 0;
	virtual void AddOnDragSubscriber(DragSubscriber& subscriber) = 0;
	virtual void RemoveOnDragSubscriber(DragSubscriber& subscriber) = 0;
};

