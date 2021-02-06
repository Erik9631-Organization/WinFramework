#pragma once
class MoveSubscriber;
class EventMoveInfo;

class MoveSubject
{
public:
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) = 0;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) = 0;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) = 0;
};

