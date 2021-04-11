#pragma once
#include "TrackBarBehavior.h"
#include "MoveSubscriber.h"
#include "ResizeSubscriber.h"
#include "OnAddSubscriber.h"
#include "EventOnAddInfo.h"
#include "Component.h"

class VerticalTrackbarBehavior : public TrackBarBehavior, public MoveSubscriber, public ResizeSubscriber, public OnAddSubscriber<Component&>
{
private:
	int lastMoseY = 0;
	void MoveTrackerByMouse(EventMouseStateInfo e);
	Adjustable* downMostComponent = nullptr;

	void UpdateDownmostComponent(Adjustable& newComponent);
	void UpdateTrackbarHeight();
	void UpdateTrackbarPos();
	void UpdateTrackerHeight();
	void MoveComponents();

public:
	void UpdateTrackbar();
	virtual void OnMouseMove(EventMouseStateInfo e) override;
	virtual void OnMouseDown(EventMouseStateInfo e) override;
	VerticalTrackbarBehavior(TrackBar& trackbar);

	// Inherited via MoveSubscriber
	virtual void OnMove(EventMoveInfo e) override;

	// Inherited via ResizeSubscriber
	virtual void OnResize(EventResizeInfo e) override;

	// Inherited via OnAddSubscriber
	virtual void OnAdd(EventOnAddInfo<Component&> e) override;
};

