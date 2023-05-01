#include "EventOnActivateInfo.h"

EventOnActivateInfo::EventOnActivateInfo(bool state, EventSource *source)
{
    this->state = state;
}

bool EventOnActivateInfo::IsActive() const
{
    return state;
}

EventSource *EventOnActivateInfo::GetSource() const
{
    return source;
}
