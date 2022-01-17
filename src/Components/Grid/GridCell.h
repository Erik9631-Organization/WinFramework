#pragma once
#include "Components/Adjustable.h"
#include "EventTypes/EventResizeInfo.h"
#include "EventTypes/EventMoveInfo.h"
#include "GridSpan.h"

class Grid;

/*
* How spanning should work:
* 1) Each GridCell should have Setspan parameter. It recieved a data type that contains grid-column-start, grid-column-end, grid-row-start, grid-row-end
* 2) When the span is set, the span parent is calculated. This is the top left cell of the entire span area.
* 3) This way, all the cells within the span will refer to the top corner.
* 4) The methods will be automatically delegated to the parent. Size and position should be an exception as the parent will use those values to calculate the spanning of its component
* The idea is that spanning should be possible with the existing grid system, without creating incompatibilities
*/

class GridCell : Adjustable
{
private:
	Grid& parentGrid;
	Adjustable* associatedAdjustable;

	Gdiplus::Size cellSize;
	Gdiplus::Point indexPos; 
	Gdiplus::Point position;
	Gdiplus::Point CalculatePixelPosition();;

	GridSpan span;

	Gdiplus::Size GetSpanSize();
public:

	void ControlAdjustable(Adjustable* associatedAdjustable);
	Adjustable* GetControlledAdjustable();

	GridCell(Grid& parentGrid);
	// Inherited via Adjustable

	GridCell* GetSpanParent(); // Can't be a variable since the parent can't exist unless the row exists
	GridCell* GetSpanCorner(); // Returns grid of the bottom right corner of the span

	void SetSpan(GridSpan span);
	GridSpan GetSpan();
	bool IsSpanParent();


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

