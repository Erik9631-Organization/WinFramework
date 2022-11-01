#pragma once
#include "api/Adjustable.h"
#include <Windows.h>
#include <gdiplus.h>
#include "Behavior/DefaultMove.h"
#include "Behavior/DefaultResize.h"
#include "DataTypes/DefaultMultiTree.h"

class UiElement;

class Viewport : public Adjustable
{
private:
	Adjustable& associatedAdjustable;
	DefaultMultiTree<Adjustable*> viewportNode; //For the default behavior

	DefaultMove<Adjustable*> moveBehavior;
	DefaultResize resizeBehavior;

    glm::vec2 absoluteSize;
    glm::vec2 absolutePosition;
    glm::vec2 internalOffset;

	float xMultiplier = 1;
	float yMultiplier = 1;
	float widthMultiplier = 1;
	float heightMultiplier = 1;

private:
	void CalculateAbsolutePosition(const glm::vec2 &relative);
	void CalculateAbsoluteSize(const glm::vec2 &size);

public:
	Viewport(Adjustable& adjustable);

	void SetXMultiplier(float x);
	void SetYMultiplier(float y);
	void SetWidthMultiplier(float width);
	void SetHeightMultiplier(float height);
	virtual float GetViewportXMultiplier();
	virtual float GetViewportYMultiplier();
	virtual float GetViewportWidthMultiplier();
	virtual float GetViewportHeightMultiplier();

	virtual int GetViewportAbsoluteWidth();
	virtual int GetViewportAbsoluteHeight();
	virtual glm::vec2 GetViewportAbsoluteSize();

	// Inherited via Movable
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	virtual glm::vec2 GetPosition() override;
	virtual float GetX() override;
	virtual float GetY() override;
	virtual float GetAbsoluteX() override;
	virtual float GetAbsoluteY() override;
	virtual glm::vec2 GetAbsolutePosition() override;
	virtual void SetPosition(const glm::vec2 &position) override;
	virtual void SetPosition(float x, float y) override;
	virtual void SetX(float x) override;
	virtual void SetY(float y) override;

	// Inherited via Resizable
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual glm::vec2 GetSize() override;
	virtual float GetWidth() override;
	virtual float GetHeight() override;
	virtual void SetSize(const glm::vec2 &size, bool emit) override;
	virtual void SetSize(float width, float height, bool emit) override;
	virtual void SetWidth(float width) override;
	virtual void SetHeight(float height) override;

	// Inherited via Adjustable
	virtual void OnUpdate(EventUpdateInfo e) override;


	// Inherited via Adjustable
	virtual void SetTranslate(const glm::vec2 &offset) override;

	virtual void SetTranslateX(float x) override;

	virtual void SetTranslateY(float y) override;

	virtual glm::vec2 GetTranslate() override;

	virtual float GetTranslateX() override;

	virtual float GetTranslateY() override;

};

