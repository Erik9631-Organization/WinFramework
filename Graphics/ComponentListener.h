#pragma once
class EventResizeInfo;
class EventMoveInfo;
class EventHoverInfo;
class EventFocusInfo;

class ComponentListener
{
public:
	virtual void OnResize(EventResizeInfo eventInfo) = 0;
	virtual void OnMove(EventMoveInfo eventInfo) = 0;
	virtual void OnHover(EventHoverInfo eventInfo) = 0;
	virtual void OnFocus(EventFocusInfo eventInfo) = 0;
	ComponentListener();
	~ComponentListener();
};

