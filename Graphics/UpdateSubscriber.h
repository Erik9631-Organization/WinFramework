#pragma once
class EventUpdateInfo;

class UpdateSubscriber
{
public:
	virtual void OnUpdate(EventUpdateInfo e) = 0;
};

