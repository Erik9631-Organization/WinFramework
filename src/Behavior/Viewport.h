#pragma once
#include "Components/Adjustable.h"
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
	DefaultMultiTree<Adjustable&> viewportNode; //For the default behavior

	DefaultMove<Adjustable&> moveBehavior;
	DefaultResize resizeBehavior;

	Gdiplus::Size absoluteSize;
	Gdiplus::Point absolutePosition;
	Gdiplus::Point internalOffset;

	float xMultiplier = 1;
	float yMultiplier = 1;
	float widthMultiplier = 1;
	float heightMultiplier = 1;

private:
	void CalculateAbsolutePosition(Gdiplus::Point relative);
	void CalculateAbsoluteSize(Gdiplus::Size size);

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
	virtual Gdiplus::Size GetViewportAbsoluteSize();

	// Inherited via Movable
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

	// Inherited via Resizable
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

	// Inherited via Adjustable
	virtual void OnUpdate(EventUpdateInfo e) override;


	// Inherited via Adjustable
	virtual void SetTranslate(Gdiplus::Point offset) override;

	virtual void SetTranslateX(int x) override;

	virtual void SetTranslateY(int y) override;

	virtual Gdiplus::Point GetTranslate() override;

	virtual int GetTranslateX() override;

	virtual int GetTranslateY() override;

};

