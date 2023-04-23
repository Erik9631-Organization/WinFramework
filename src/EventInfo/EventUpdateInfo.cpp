#include "EventUpdateInfo.h"


EventUpdateInfo::EventUpdateInfo(EventUpdateFlags flags)
{
	updateFlags = flags;
}

void EventUpdateInfo::SetFlags(EventUpdateFlags flags)
{
	updateFlags = flags;
}

void EventUpdateInfo::DisableFlag(EventUpdateFlags flags)
{
	updateFlags = updateFlags & (~flags);
}

bool EventUpdateInfo::HasFlag(EventUpdateFlags flag)
{
	return (bool)(updateFlags & flag);
}
