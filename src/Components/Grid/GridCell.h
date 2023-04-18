#pragma once
#include "api/Adjustable.h"
#include "EventTypes/EventResizeInfo.h"
#include "EventTypes/EventMoveInfo.h"
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
	glm::ivec2 indexPos;
    glm::vec2 position;
    glm::ivec2 CalculatePixelPosition();;

	GridSpan span;

	glm::ivec2 GetSpanSize();

    void SetPosition(glm::vec4 position) override;

    void SetPosition(float x, float y, float z, float w) override;

    void SetX(float x) override;

    void SetY(float y) override;

    void SetTranslate(glm::vec4 offset) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y) override;

    void SetSize(glm::vec4 size) override;

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


	void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	const glm::vec4 & GetSize() override;
	float GetWidth() override;
	float GetHeight() override;
	void SetSize(const glm::vec4 &size, bool emit) override;
	void SetSize(float width, float height, bool emit) override;
	void SetWidth(float width, bool emit) override;
	void SetHeight(float height, bool emit) override;
	void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	glm::vec4 GetPosition() override;
	float GetX() override;
	float GetY() override;
    float GetZ() override;
    float GetW() override;
	float GetAbsoluteX() override;
	float GetAbsoluteY() override;
	const glm::vec4 & GetAbsolutePosition() override;
	void SetPosition(glm::vec4 position, bool emit) override;
	void SetPosition(float x, float y, float z, float w, bool emit) override;
	void SetX(float x, bool emit) override;
	void SetY(float y, bool emit) override;
    void SetZ(float z, bool emit) override;
    void SetZ(float z) override;
    void SetW(float w, bool emit) override;
    void SetW(float w) override;
	void SetTranslate(glm::vec4 offset, bool emit) override;
	void SetTranslateX(float x, bool emit) override;
	void SetTranslateY(float y, bool emit) override;
	glm::vec4 GetTranslate() override;
	float GetTranslateX() override;
	float GetTranslateY() override;
	void OnUpdate(EventUpdateInfo e) override;
	int GetPixelX();
	int GetPixelY();
	glm::vec2 GetPixelPosition();
};

