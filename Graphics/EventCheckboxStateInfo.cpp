#include "EventCheckboxStateInfo.h"

EventCheckboxStateInfo::EventCheckboxStateInfo(std::any src, bool state)
{
	this->src = src;
	this->state = state;
}

bool EventCheckboxStateInfo::GetState()
{
	return state;
}

std::any EventCheckboxStateInfo::GetSrc()
{
	return src;
}
