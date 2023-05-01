#include "EventRadioButtonStateInfo.h"

EventRadioButtonStateInfo::EventRadioButtonStateInfo(bool selected, EventSource *src)
{
	this->isSelected = selected;
	this->src = src;
}

bool EventRadioButtonStateInfo::IsSelected() const
{
	return isSelected;
}

EventSource * EventRadioButtonStateInfo::GetSource() const
{
    return src;
}
