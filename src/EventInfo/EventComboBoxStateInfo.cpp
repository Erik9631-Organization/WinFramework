#include "EventComboBoxStateInfo.h"
#include "ComboBoxStateSubject.h"

EventComboBoxStateInfo::EventComboBoxStateInfo(ComboElement* element, ComboBoxStateSubject *src) : element(element), src(src)
{

}

ComboElement* EventComboBoxStateInfo::GetElement()
{
    return element;
}

EventSource *EventComboBoxStateInfo::GetSource() const
{
    return src;
}
