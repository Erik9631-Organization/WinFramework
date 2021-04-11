#include "TrackBarBehavior.h"
#include "EventMouseStateInfo.h"
#include "TrackBar.h"
#include "CoreWindowFrame.h"
#include "EventResizeInfo.h"
#include "EventMoveInfo.h"

Gdiplus::Color TrackBarBehavior::PopColorState(std::vector<std::pair<std::string, Gdiplus::Color>>::iterator it)
{
		Gdiplus::Color color = it->second;
		colorStates.erase(it, colorStates.end());
		return color;
}

Gdiplus::Color TrackBarBehavior::PopColorState(std::string stateName)
{
	std::vector<std::pair<std::string, Gdiplus::Color>>::iterator it = ContainsColorState(stateName);
	if (it != colorStates.end())
		return PopColorState(it);
}

std::vector<std::pair<std::string, Gdiplus::Color>>::iterator TrackBarBehavior::ContainsColorState(std::string stateName)
{
	for (std::vector<std::pair<std::string, Gdiplus::Color>>::iterator it = colorStates.begin(); it != colorStates.end(); it++)
		if (stateName.compare(it->first) == 0)
			return it;
	return colorStates.end();
}

bool TrackBarBehavior::CheckTrackerCollision(Gdiplus::Point point)
{
	float trackerYPos = associatedTrackbar.GetPropery<float>("get-tracker-position") * associatedTrackbar.GetHeight();
	float trackerHeight = associatedTrackbar.GetPropery<float>("get-tracker-height") * associatedTrackbar.GetHeight();

	if (point.Y > trackerYPos && point.Y < trackerYPos + trackerHeight)
		return true;
	return false;
}

bool TrackBarBehavior::IsSelected()
{
	return isSelected;
}

bool TrackBarBehavior::IsHighlighted()
{
	return isHighlighted;
}

TrackBar& TrackBarBehavior::GetAssociatedTrackbar()
{
	return associatedTrackbar;
}

void TrackBarBehavior::HighlightTrackbar(Gdiplus::Point mousePos)
{
	if (CheckTrackerCollision(mousePos))
	{
		if (isHighlighted == false)
		{
			colorStates.push_back(std::make_pair("onHighlighted", associatedTrackbar.GetPropery<Gdiplus::Color>("get-tracker-color")));
			associatedTrackbar.SetProperty("tracker-color", Gdiplus::Color::MakeARGB(255, 50, 50, 50));
		}
		isHighlighted = true;
	}
	else
	{
		UnHighlightTrackbar();
	}
}

void TrackBarBehavior::UnHighlightTrackbar()
{
	if (isHighlighted == false)
		return;
	if (isSelected == true)
		return;

	std::vector<std::pair<std::string, Gdiplus::Color>>::iterator it = ContainsColorState("onHighlighted");
	if (it == colorStates.end())
		return;

	associatedTrackbar.SetProperty("tracker-color", PopColorState(it));
	isHighlighted = false;
	isSelected = false;
}


void TrackBarBehavior::SelectTrackbar(Gdiplus::Point mousePos)
{
	if (CheckTrackerCollision(mousePos))
	{
		if (isSelected == false)
		{
			colorStates.push_back(std::make_pair("onSelected", associatedTrackbar.GetPropery<Gdiplus::Color>("get-tracker-color")));
			associatedTrackbar.SetProperty("tracker-color", Gdiplus::Color::MakeARGB(255, 100, 100, 100));
		}
		isSelected = true;
	}
	else
	{
		if (isSelected)
		{
			associatedTrackbar.SetProperty("tracker-color", PopColorState("onSelected"));
			isSelected = false;
		}

	}
}

void TrackBarBehavior::UnSelectTrackbar()
{
	if (isSelected == false)
		return;

	std::vector<std::pair<std::string, Gdiplus::Color>>::iterator it = ContainsColorState("onSelected");
	if (it == colorStates.end())
		return;

	associatedTrackbar.SetProperty("tracker-color", PopColorState(it));
	isSelected = false;
}




TrackBarBehavior::TrackBarBehavior(TrackBar& trackbar) : associatedTrackbar(trackbar)
{
	associatedTrackbar.SetPercentualHeight(0.2f);
	associatedTrackbar.AddMouseStateSubscriber(*this);
}

void TrackBarBehavior::OnMouseDown(EventMouseStateInfo e)
{
	if (e.GetSrc() == &associatedTrackbar)
		SelectTrackbar(e.GetMousePosition());
}

void TrackBarBehavior::OnMouseUp(EventMouseStateInfo e)
{
	UnSelectTrackbar();
	if (e.GetSrc() != &associatedTrackbar)
		UnHighlightTrackbar();
}

void TrackBarBehavior::OnMousePressed(EventMouseStateInfo e)
{

}

void TrackBarBehavior::OnMouseMove(EventMouseStateInfo e)
{
	if (e.GetSrc() == &associatedTrackbar)
		HighlightTrackbar(e.GetMousePosition());
	//Also move the components
}

void TrackBarBehavior::OnMouseEntered(EventMouseStateInfo e)
{

}

void TrackBarBehavior::OnMouseLeft(EventMouseStateInfo e)
{
	if(e.GetSrc() == &associatedTrackbar)
		UnHighlightTrackbar();
}
