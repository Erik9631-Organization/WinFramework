#pragma once
class EventMoveInfo;

class MoveSubscriber
{
public:
	virtual void OnMove(EventMoveInfo e) = 0;
};

