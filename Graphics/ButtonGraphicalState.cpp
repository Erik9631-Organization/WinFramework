#include "EventMouseStateInfo.h"
#include "Button.h"
ButtonGraphicalState::ButtonGraphicalState(Button& button) : associatedButton(button)
{
	associatedButton.AddMouseStateSubscriber(*this);
	onHoverColor = Color::MakeARGB(255, 100, 100, 100);
	onClickColor = Color::MakeARGB(255, 60, 60, 60);
}

void ButtonGraphicalState::SetOnHoverColor(Gdiplus::Color color)
{
	onHoverColor = color;
}

void ButtonGraphicalState::SetOnClickColor(Gdiplus::Color color)
{
	onClickColor = color;
}


void ButtonGraphicalState::OnMouseDown(EventMouseStateInfo e)
{
	previousOnClickColor = associatedButton.GetBackgroundColor();
	associatedButton.SetBackgroundColor(onClickColor);
}

void ButtonGraphicalState::OnMouseUp(EventMouseStateInfo e)
{
	associatedButton.SetBackgroundColor(previousOnClickColor);
}

void ButtonGraphicalState::OnMousePressed(EventMouseStateInfo e)
{
}

void ButtonGraphicalState::OnMouseMove(EventMouseStateInfo e)
{

}

void ButtonGraphicalState::OnMouseEntered(EventMouseStateInfo e)
{
	previousOnHoverColor = associatedButton.GetBackgroundColor();
	associatedButton.SetBackgroundColor(onHoverColor);
}

void ButtonGraphicalState::OnMouseLeft(EventMouseStateInfo e)
{
	associatedButton.SetBackgroundColor(previousOnHoverColor);
}
