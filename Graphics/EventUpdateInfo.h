#pragma once
#include "EventUpdateFlags.h"

class EventUpdateInfo
{
public:

	EventUpdateInfo(EventUpdateFlags flags);
	void SetFlags(EventUpdateFlags flags);
	void DisableFlag(EventUpdateFlags flags);
	bool HasFlag(EventUpdateFlags flag);
private:
	EventUpdateFlags updateFlags;
};

