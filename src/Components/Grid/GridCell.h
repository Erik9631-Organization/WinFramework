#pragma once
#include "api/Adjustable.h"
#include "EventTypes/EventResizeInfo.h"
#include "EventTypes/EventMoveInfo.h"
#include "GridSpan.h"
#include "Vector2Int.h"
#include "vec2.hpp"

class Grid;

/*
* How spanning should work:
* 1) Each GridCell should have Setspan parameter. It recieved a data type that contains grid-column-start, grid-column-end, grid-row-start, grid-row-end
* 2) When the span is set, the span parent is calculated. This is the top left cell of the entire span area.
* 3) This way, all the cells within the span will refer to the top corner.
* 4) The methods will be automatically delegated to the parent. Size and position should be an exception as the parent will use those values to calculate the spanning of its component
* The idea is that spanning should be possible with the existing grid system, without creating incompatibilities
*/

class GridCell : public Adjustable
{
private:
	Grid& parentGrid;
	Adjustable* associatedAdjustable = nullptr;

    glm::vec2 cellSize;
	Vector2Int indexPos;
    glm::vec2 position;
	Vector2Int CalculatePixelPosition();;

	GridSpan span;

	Vector2Int GetSpanSize();

    void SetPosition(Vector2 position) override;

    void SetPosition(float x, float y) override;

    void SetX(float x) override;

    void SetY(float y) override;

    void SetTranslate(Vector2 offset) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y) override;

    void SetSize(Vector2 size) override;

    void SetSize(float width, float height) override;

    void SetWidth(float width) override;

    void SetHeight(float height) override;

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
	virtual glm::vec2 GetSize() override;
	virtual float GetWidth() override;
	virtual float GetHeight() override;
	virtual void SetSize(const glm::vec2 &size, bool emit) override;
	virtual void SetSize(float width, float height, bool emit) override;
	virtual void SetWidth(float width, bool emit) override;
	virtual void SetHeight(float height, bool emit) override;
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	virtual glm::vec2 GetPosition() override;
	virtual float GetX() override;
	virtual float GetY() override;
	virtual float GetAbsoluteX() override;
	virtual float GetAbsoluteY() override;
	virtual Vector2 GetAbsolutePosition() override;
	virtual void SetPosition(Vector2 position, bool emit) override;
	virtual void SetPosition(float x, float y, bool emit) override;
	virtual void SetX(float x, bool emit) override;
	virtual void SetY(float y, bool emit) override;
	virtual void SetTranslate(Vector2 offset, bool emit) override;
	virtual void SetTranslateX(float x, bool emit) override;
	virtual void SetTranslateY(float y, bool emit) override;
	virtual Vector2 GetTranslate() override;
	virtual float GetTranslateX() override;
	virtual float GetTranslateY() override;
	virtual void OnUpdate(EventUpdateInfo e) override;
	int GetPixelX();
	int GetPixelY();
	glm::vec2 GetPixelPosition();
};

