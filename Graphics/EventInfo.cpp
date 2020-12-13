#include "EventInfo.h"



Component & EventInfo::GetComponent()
{
	return component;
}

EventInfo::EventInfo(Component & component) : component(component)
{
}


EventInfo::~EventInfo()
{
}
