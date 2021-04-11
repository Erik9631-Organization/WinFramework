#include "VerticalTrackbarBehavior.h"
#include "TrackBar.h"
#include "CoreWindowFrame.h"
#include "EventResizeInfo.h"
#include "EventMoveInfo.h"
#include <algorithm>

void VerticalTrackbarBehavior::MoveTrackerByMouse(EventMouseStateInfo e)
{
	if (IsSelected() == false)
		return;
	float diff = e.GetAbsoluteMouseY() - lastMoseY;

	float trackerYPos = GetAssociatedTrackbar().GetPropery<float>("get-tracker-position") * GetAssociatedTrackbar().GetHeight();
	float trackerHeight = GetAssociatedTrackbar().GetPropery<float>("get-tracker-height") * GetAssociatedTrackbar().GetHeight();

	trackerYPos += diff;

	//Check if bounding
	if (trackerYPos < 0)
		trackerYPos = 0;

	if (trackerYPos + trackerHeight > GetAssociatedTrackbar().GetHeight())
		trackerYPos = GetAssociatedTrackbar().GetHeight() - trackerHeight;



	GetAssociatedTrackbar().SetProperty<float>("tracker-position", trackerYPos / (float)GetAssociatedTrackbar().GetHeight());
	lastMoseY = e.GetAbsoluteMouseY();
}

void VerticalTrackbarBehavior::UpdateDownmostComponent(Adjustable& newMovable)
{
	if (newMovable.GetY() + newMovable.GetHeight() < GetAssociatedTrackbar().GetWidth())
		return;

	if (downMostComponent == nullptr)
	{
		downMostComponent = &newMovable;
		return;
	}
	if (newMovable.GetY() + newMovable.GetHeight() > downMostComponent->GetY() + downMostComponent->GetHeight())
		downMostComponent = &newMovable;
}

void VerticalTrackbarBehavior::UpdateTrackbarHeight()
{
	if (GetAssociatedTrackbar().GetParent() == nullptr)
		return;
	GetAssociatedTrackbar().SetHeight(GetAssociatedTrackbar().GetParent()->GetHeight());
}

void VerticalTrackbarBehavior::UpdateTrackbarPos()
{
	if (GetAssociatedTrackbar().GetParent() == nullptr)
		return;
	GetAssociatedTrackbar().SetX(GetAssociatedTrackbar().GetParent()->GetWidth() - GetAssociatedTrackbar().GetWidth());
	GetAssociatedTrackbar().SetY(0);
}

void VerticalTrackbarBehavior::UpdateTrackerHeight()
{
	if (downMostComponent == nullptr)
		return;
	float y = downMostComponent->GetY();
	float height = downMostComponent->GetHeight();
	float shit = GetAssociatedTrackbar().GetHeight();
	float trackerHeight = (float)GetAssociatedTrackbar().GetHeight() / ((float)downMostComponent->GetY() + (float)downMostComponent->GetHeight());
	trackerHeight = std::clamp<float>(trackerHeight, 0.1f, 1.0f);
	GetAssociatedTrackbar().SetProperty("tracker-height", trackerHeight);
}

void VerticalTrackbarBehavior::MoveComponents()
{
	if (downMostComponent == nullptr)
		return;
	float moveInterval = downMostComponent->GetHeight() + downMostComponent->GetY() - GetAssociatedTrackbar().GetHeight();
	float trackerMovementToHeightRatio = 1 / (1 - GetAssociatedTrackbar().GetPropery<float>("get-tracker-height"));
	float yOffset = (trackerMovementToHeightRatio * GetAssociatedTrackbar().GetPropery<float>("get-tracker-position")) * moveInterval;
	
	if(GetAssociatedTrackbar().GetControlledComponent() != nullptr)
		GetAssociatedTrackbar().GetControlledComponent()->SetInternalOffset(Point(0, -yOffset));
}

void VerticalTrackbarBehavior::UpdateTrackbar()
{
	UpdateTrackbarHeight();
	UpdateTrackbarPos();
}

void VerticalTrackbarBehavior::OnMouseMove(EventMouseStateInfo e)
{
	TrackBarBehavior::OnMouseMove(e); // Super
	if (!IsSelected())
		return;
	MoveTrackerByMouse(e);
	MoveComponents();
}

void VerticalTrackbarBehavior::OnMouseDown(EventMouseStateInfo e)
{
	TrackBarBehavior::OnMouseDown(e);
	if (IsSelected() == true)
		lastMoseY = e.GetAbsoluteMouseY();
}

VerticalTrackbarBehavior::VerticalTrackbarBehavior(TrackBar& trackbar) : TrackBarBehavior(trackbar)
{

}

void VerticalTrackbarBehavior::OnMove(EventMoveInfo e)
{
	Movable* movable = e.GetSrc();

	Adjustable* adjustable = dynamic_cast<Adjustable*>(movable);
	if (adjustable != nullptr)
		UpdateDownmostComponent(*adjustable);
}

void VerticalTrackbarBehavior::OnResize(EventResizeInfo e)
{
	Resizable* resizable = e.GetSrc();

	if (GetAssociatedTrackbar().GetParent() != nullptr && GetAssociatedTrackbar().GetParent() == resizable)
		UpdateTrackbar();
	else
	{
		Adjustable* adjustable = dynamic_cast<Adjustable*>(resizable);
		if (adjustable != nullptr)
			UpdateDownmostComponent(*adjustable);
	}

}

void VerticalTrackbarBehavior::OnAdd(EventOnAddInfo<Component&> e)
{
	e.GetAddedComponent().AddOnMoveSubscriber(*this);
	e.GetAddedComponent().AddOnResizeSubscriber(*this);
	UpdateDownmostComponent(e.GetAddedComponent());
	UpdateTrackerHeight();
}
