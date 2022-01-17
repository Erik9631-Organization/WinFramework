#pragma once
class EventMouseStateInfo;

class MouseStateSubscriber
{
public:
	virtual void OnMouseDown(EventMouseStateInfo e) = 0;
	virtual void OnMouseUp(EventMouseStateInfo e) = 0;
	virtual void OnMousePressed(EventMouseStateInfo e) = 0;
	virtual void OnMouseMove(EventMouseStateInfo e) = 0;
	virtual void OnMouseEntered(EventMouseStateInfo e) = 0;
	virtual void OnMouseLeft(EventMouseStateInfo e) = 0;
	virtual void OnMouseCaptured(EventMouseStateInfo e) = 0;
};

