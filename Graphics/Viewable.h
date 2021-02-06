#pragma once
#include <Windows.h>
#include <gdiplus.h>
class MoveSubscriber;
class EventResizeInfo;
class ResizeSubscriber;
class EventMoveInfo;

class Viewable
{
	virtual void AddOnViewportMoveSubscriber(MoveSubscriber& subscriber) = 0;
	virtual void RemoveOnViewportMoveSubscriber(MoveSubscriber& subscriber) = 0;
	virtual void NotifyOnViewportMoveSubscribers(EventMoveInfo event) = 0;

	virtual void SetViewportXMultiplier(float x) = 0;
	virtual void SetViewportYMultiplier(float y) = 0;
	virtual void SetViewportWidthMultiplier(float width) = 0;
	virtual void SetViewportHeightMultiplier(float height) = 0;
	virtual float GetViewportXMultiplier() = 0;
	virtual float GetViewportYMultiplier() = 0;
	virtual float GetViewportWidthMultiplier() = 0;
	virtual float GetViewportHeightMultiplier() = 0;

	virtual void SetViewportXOffset(int x) = 0;
	virtual void SetViewportYOffset(int y) = 0;
	virtual void SetViewportOffset(Gdiplus::Point offset) = 0;
	virtual int GetViewportAbsoluteX() = 0;
	virtual int GetViewportAbsoluteY() = 0;
	virtual Gdiplus::Point GetViewportAbsolutePosition() = 0;
	virtual int GetViewportX() = 0;
	virtual int GetViewportY() = 0;
	virtual Gdiplus::Point GetViewportPosition() = 0;

	virtual void NotifyOnViewportResizeSubscribers(EventResizeInfo event) = 0;
	virtual void AddOnViewportResizeSubscriber(ResizeSubscriber& subscriber) = 0;
	virtual void RemoveOnViewportResizeSubscriber(ResizeSubscriber& subscriber) = 0;

	virtual int GetViewportWidth() = 0;;
	virtual int GetViewportHeight() = 0;
	virtual void SetViewportSize(Gdiplus::Size size) = 0;
	virtual void SetViewportSize(int width, int height) = 0;
	virtual void SetViewportWidth(int width) = 0;
	virtual void SetViewportHeight(int height) = 0;
	virtual int GetViewportAbsoluteWidth() = 0;
	virtual int GetViewportAbsoluteHeight() = 0;
	virtual Gdiplus::Size GetViewportAbsoluteSize() = 0;
	virtual Gdiplus::Size GetViewportSize() = 0;
};

