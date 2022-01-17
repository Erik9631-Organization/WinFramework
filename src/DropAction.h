#pragma once
#include "Events/DropSubscriber.h"

template<class DroppableType>
class DropAction : public DropSubscriber
{
	virtual void Init(DroppableType associatedDropType) = 0;
};

