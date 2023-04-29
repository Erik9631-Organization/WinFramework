#pragma once
#include "Adjustable.h"
#include "EventResizeInfo.h"
#include "EventMoveInfo.h"
#include "GridSpan.h"
#include "vec2.hpp"

class Grid;

/*
* How spanning should work:
* 1) Each GridCell should have Setspan parameter. It recieved a data type that contains grid-column-start, grid-column-end, grid-row-start, grid-row-end
* 2) When the span is set, the span parent is calculated. This is the top left cell of the entire span area.
* 3) This way, all the cells within the span will refer to the top corner.
* 4) The methods will be automatically delegated to the parent. Size and viewPortSize should be an exception as the parent will use those values to calculate the spanning of its component
* The idea is that spanning should be possible with the existing grid system, without creating incompatibilities
*/

class GridCell : public Adjustable
{
private:
	Grid& parentGrid;
	Adjustable* associatedAdjustable = nullptr;

    glm::vec2 cellSize;
	glm::vec3 indexPos = {0, 0, 0};
    glm::vec2 position;
    glm::vec4 absPos;
    glm::ivec2 CalculatePixelPosition();;

	GridSpan span;

	glm::ivec2 GetSpanSize();
public:

	void ControlAdjustable(Adjustable* associatedAdjustable);
	Adjustable* GetControlledAdjustable();

	explicit GridCell(Grid& parentGrid);
	// Inherited via Adjustable

	GridCell* GetSpanParent(); // Can't be a variable since the parent can't exist unless the row exists
	GridCell* GetSpanCorner(); // Returns grid of the bottom right corner of the span

	void SetSpan(GridSpan span);
	GridSpan GetSpan();
	bool IsSpanParent();


	void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	const glm::vec3 & GetSize() const override;
	void SetSize(const glm::vec3 &size, bool emit = true) override;
	void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	void NotifyOnMoveSubscribers(const EventMoveInfo &event) override;
	[[nodiscard]] const glm::vec3 & GetPosition() const override;
	[[nodiscard]] const glm::vec3 & GetAbsolutePosition() const override;
	void SetPosition(const glm::vec3 &position, bool emit = true) override;
	void SetTranslate(const glm::vec3 &offset, bool emit = true) override;
	void OnUpdate(EventUpdateInfo e) override;
	int GetPixelX();
	int GetPixelY();
	glm::vec2 GetPixelPosition();
    [[nodiscard]] const glm::vec3 & GetTranslate() const override;
};

