#pragma once
#include <ctime>
#include <chrono>
enum ComponentEvent;
enum EventModifiers;
class EventInfo
{
private:
	ComponentEvent id;
	long long timeStamp;
	EventModifiers modifiers;

public:
	ComponentEvent GetEventId();
	long long GetTimeStamp();
	EventModifiers GetModifiers();
	
	EventInfo(ComponentEvent eventId, EventModifiers modifiers);
	~EventInfo();
};

