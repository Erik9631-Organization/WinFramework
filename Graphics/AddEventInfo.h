#pragma once
#include "EventInfo.h"
class Component;
class AddEventInfo : EventInfo
{
public:
	AddEventInfo(Component & addedComponent);
	Component * GetParentComponent();
	~AddEventInfo();
};

