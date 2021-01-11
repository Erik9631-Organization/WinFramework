#pragma once
class EventMouseStateInfo;

class MouseStateSubscriber
{
	virtual void OnMouseDown(EventMouseStateInfo e) = 0;
	virtual void OnMouseUp(EventMouseStateInfo e) = 0;
	virtual void OnMousePressed(EventMouseStateInfo e) = 0;
	virtual void OnMouseMove(EventMouseStateInfo e) = 0;
};

