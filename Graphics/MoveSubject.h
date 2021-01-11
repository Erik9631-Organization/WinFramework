#pragma once
class MovableSubscriber;
class EventMoveInfo;

class MoveSubject
{
	virtual void AddOnMoveSubscriber(MovableSubscriber& subscriber) = 0;
	virtual void AddOnRemoveSubscriber(MovableSubscriber& subscriber) = 0;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) = 0;
};

