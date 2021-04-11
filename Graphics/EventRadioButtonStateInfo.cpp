#include "EventRadioButtonStateInfo.h"

EventRadioButtonStateInfo::EventRadioButtonStateInfo(bool selected, std::any src)
{
	this->isSelected = selected;
	this->src = src;
}

std::any EventRadioButtonStateInfo::GetSrc()
{
	return src;
}

bool EventRadioButtonStateInfo::IsSelected()
{
	return isSelected;
}
