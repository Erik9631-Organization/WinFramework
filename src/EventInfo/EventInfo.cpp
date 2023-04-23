#include "EventInfo.h"



UiElement & EventInfo::GetComponent()
{
	return component;
}

EventInfo::EventInfo(UiElement & component) : component(component)
{
}


EventInfo::~EventInfo()
{
}
