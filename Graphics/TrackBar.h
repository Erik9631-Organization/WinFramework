#pragma once
/*
* Trackbar can control any component. (Since all components have a viewport).
* It will automatically calculate its own width and movement ratio based on the component's downmost child 
*/
#include "Component.h"
#include "TrackbarGraphics.h"
#include "VerticalTrackbarBehavior.h"

class TrackBar : public Component
{
private:
	TrackbarGraphics graphics;
	VerticalTrackbarBehavior behavior;
	Component* componentToControl;
public:
	TrackBar();
	TrackBar(std::string name);
	TrackBar(int x, int y, int width, int height, std::string name);
	void SetPercentualHeight(float height);
	void SetPercentualPosition(float posY);
	void SetTrackerColor(Gdiplus::Color color);
	void Control(Component& componentToControl);
	Component* GetControlledComponent();
};

