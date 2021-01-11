#pragma once
class EventMoveInfo;

class MovableSubscriber
{
	virtual void OnMove(EventMoveInfo e) = 0;
};

