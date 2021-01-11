#pragma once
class EventResizeInfo;
class ResizeSubscriber
{
	virtual void OnResize(EventResizeInfo event) = 0;
};

