#pragma once
#include "Events/MouseStateSubscriber.h"
#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include <utility>
#include <string>
#include "Components/Collidable.h"

class TrackBar;

class TrackBarBehavior : public MouseStateSubscriber
{
private:
	Gdiplus::Color PopColorState(std::vector<std::pair<std::string, Gdiplus::Color>>::iterator it);
	Gdiplus::Color PopColorState(std::string stateName);
	std::vector<std::pair<std::string, Gdiplus::Color>>::iterator ContainsColorState(std::string stateName);

	void SelectTrackbar(Gdiplus::Point mousePos);
	TrackBar& associatedTrackbar;

	bool isSelected = false;
	bool isHighlighted = false;

	void HighlightTrackbar(Gdiplus::Point mousePos);
	void UnSelectTrackbar();
	void UnHighlightTrackbar();

	std::vector<std::pair<std::string, Gdiplus::Color>> colorStates;
protected:
	bool CheckTrackerCollision(Gdiplus::Point point);
	bool IsSelected();
	bool IsHighlighted();
	TrackBar& GetAssociatedTrackbar();
public:
	TrackBarBehavior(TrackBar& trackbar);

	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;

	virtual void OnMouseUp(EventMouseStateInfo e) override;

	virtual void OnMousePressed(EventMouseStateInfo e) override;

	virtual void OnMouseMove(EventMouseStateInfo e) override;

	virtual void OnMouseEntered(EventMouseStateInfo e) override;

	virtual void OnMouseLeft(EventMouseStateInfo e) override;

    void OnMouseCaptured(EventMouseStateInfo e) override;


};

