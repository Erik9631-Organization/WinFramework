#include "EventInfo.h"
#include "ComponentEventIds.h"
#include "EventModifierIds.h"

ComponentEvent EventInfo::GetEventId()
{
	return id;
}

long long EventInfo::GetTimeStamp()
{
	return timeStamp;
}

EventModifiers EventInfo::GetModifiers()
{
	return modifiers;
}

EventInfo::EventInfo(ComponentEvent eventId, EventModifiers modifiers)
{
	id = eventId;
	this->modifiers = modifiers;
	this->timeStamp = std::chrono::system_clock::now().time_since_epoch().count();
}

EventInfo::~EventInfo()
{
}
