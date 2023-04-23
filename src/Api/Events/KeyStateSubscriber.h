#pragma once
class EventKeyStateInfo;

class KeyStateSubscriber
{
public:
	virtual void OnKeyDown(EventKeyStateInfo e) = 0;
	virtual void OnKeyUp(EventKeyStateInfo e) = 0;
	virtual void OnKeyPressed(EventKeyStateInfo e) = 0;
};

