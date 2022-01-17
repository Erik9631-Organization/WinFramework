#include "EventCheckboxStateInfo.h"

EventCheckboxStateInfo::EventCheckboxStateInfo(CheckboxStateSubject* src, bool state)
{
	this->src = src;
	this->state = state;
}

bool EventCheckboxStateInfo::GetState()
{
	return state;
}

CheckboxStateSubject* EventCheckboxStateInfo::GetSrc()
{
	return src;
}
