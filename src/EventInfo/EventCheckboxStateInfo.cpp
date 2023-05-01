#include "EventCheckboxStateInfo.h"

EventCheckboxStateInfo::EventCheckboxStateInfo(EventSource *src, bool state)
{
	this->source = src;
	this->state = state;
}

bool EventCheckboxStateInfo::GetState() const
{
	return state;
}

EventSource * EventCheckboxStateInfo::GetSource() const
{
    return source;
}
