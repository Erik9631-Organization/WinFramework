#pragma once
#include "Adjustable.h"
#include "EventResizeInfo.h"
#include "EventMoveInfo.h"
class Grid;

class GridCell : Adjustable
{
private:
	Grid& parentGrid;
	Adjustable* associatedAdjustable;
	Gdiplus::Size cellSize;
	Gdiplus::Point indexPos; 
	Gdiplus::Point position;
	Gdiplus::Point CalculatePixelPosition();
public:

	void ControlAdjustable(Adjustable* associatedAdjustable);
	Adjustable* GetControlledAdjustable();

	GridCell(Grid& parentGrid);
	// Inherited via Adjustable
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual Gdiplus::Size GetSize() override;
	virtual int GetWidth() override;
	virtual int GetHeight() override;
	virtual void SetSize(Gdiplus::Size size) override;
	virtual void SetSize(int width, int height) override;
	virtual void SetWidth(int width) override;
	virtual void SetHeight(int height) override;
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	virtual Gdiplus::Point GetPosition() override;
	virtual int GetX() override;
	virtual int GetY() override;
	virtual int GetAbsoluteX() override;
	virtual int GetAbsoluteY() override;
	virtual Gdiplus::Point GetAbsolutePosition() override;
	virtual void SetPosition(Gdiplus::Point position) override;
	virtual void SetPosition(int x, int y) override;
	virtual void SetX(int x) override;
	virtual void SetY(int y) override;
	virtual void SetElementOffset(Gdiplus::Point offset) override;
	virtual void SetElementXOffset(int x) override;
	virtual void SetElementYOffset(int y) override;
	virtual Gdiplus::Point GetElementOffset() override;
	virtual int GetElementXOffset() override;
	virtual int GetElementYOffset() override;
	virtual void OnUpdate(EventUpdateInfo e) override;
	int GetPixelX();
	int GetPixelY();
	Gdiplus::Point GetPixelPosition();
};

