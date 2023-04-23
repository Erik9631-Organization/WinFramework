#include "EventRadioButtonStateInfo.h"

EventRadioButtonStateInfo::EventRadioButtonStateInfo(bool selected, RadioButtonStateSubject* src)
{
	this->isSelected = selected;
	this->src = src;
}

RadioButtonStateSubject* EventRadioButtonStateInfo::GetSrc()
{
	return src;
}

bool EventRadioButtonStateInfo::IsSelected()
{
	return isSelected;
}
