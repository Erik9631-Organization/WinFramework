#include "EventComboBoxStateInfo.h"

EventComboBoxStateInfo::EventComboBoxStateInfo(ComboElement* element, ComboBoxStateSubject& src) : element(element), src(src)
{
}

ComboElement* EventComboBoxStateInfo::GetElement()
{
    return element;
}

ComboBoxStateSubject& EventComboBoxStateInfo::GetSrc()
{
    return src;
}
