#include "TrackBar.h"

TrackBar::TrackBar() : TrackBar(0, 0, 0, 0, "")
{

}

TrackBar::TrackBar(std::string name) : TrackBar(0, 0, 0, 0, name)
{

}

TrackBar::TrackBar(int x, int y, int width, int height, std::string name) : Component(x, y, width, height, name), behavior(*this), componentToControl(nullptr)
{
	SetIgnoreOffset(true);
	AddRenderable(graphics);
}

void TrackBar::SetPercentualHeight(float height)
{
	graphics.SetPercentualHeight(height);
}

void TrackBar::SetPercentualPosition(float posY)
{
	graphics.SetPercentualPosition(posY);
}

void TrackBar::SetTrackerColor(Gdiplus::Color color)
{
}

void TrackBar::Control(Component& componentToControl)
{
	this->componentToControl = &componentToControl;
	componentToControl.AddMouseStateSubscriber(behavior);
	componentToControl.AddOnResizeSubscriber(behavior);
	componentToControl.AddOnAddSubscriber(behavior);
	behavior.UpdateTrackbar();
}

Component* TrackBar::GetControlledComponent()
{
	return componentToControl;
}
