#pragma once
class EventOnActivateInfo;

class ActivateSubscriber
{
public:
	virtual void OnActiveStateChanged(EventOnActivateInfo) = 0;
};