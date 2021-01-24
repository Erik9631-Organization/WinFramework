#pragma once
class EventResizeInfo;
class ResizeSubscriber
{
public:
	virtual void OnResize(EventResizeInfo e) = 0;
};

