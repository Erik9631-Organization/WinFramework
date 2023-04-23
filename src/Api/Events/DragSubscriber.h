#pragma once
#include "EventOnDragInfo.h"

class DragSubscriber
{
public:
	virtual void OnDragStart(EventOnDragInfo e) = 0;
	virtual void OnDragEnd(EventOnDragInfo e) = 0;
};

