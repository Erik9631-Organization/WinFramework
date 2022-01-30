#include "EventTypes/EventMouseStateInfo.h"
#include "Components/Button.h"
DefaultButtonBehavior::DefaultButtonBehavior(Button& button) : associatedButton(button)
{
	associatedButton.AddMouseStateSubscriber(*this);
	onHoverColor = {100, 100, 100};
	onClickColor = {60, 60, 60};
}

void DefaultButtonBehavior::SetOnHoverColor(Vector3 color)
{
	onHoverColor = color;
}

void DefaultButtonBehavior::SetOnClickColor(Vector3 color)
{
	onClickColor = color;
}


void DefaultButtonBehavior::OnMouseDown(EventMouseStateInfo e)
{
	associatedButton.SetColor(onClickColor);
}

void DefaultButtonBehavior::OnMouseUp(EventMouseStateInfo e)
{
    if(associatedButton.HasMouseEntered())
        associatedButton.SetColor(onHoverColor);
    else
        associatedButton.SetColor(standardColor);
}

void DefaultButtonBehavior::OnMousePressed(EventMouseStateInfo e)
{
}

void DefaultButtonBehavior::OnMouseMove(EventMouseStateInfo e)
{

}

void DefaultButtonBehavior::OnMouseEntered(EventMouseStateInfo e)
{
    if(associatedButton.IsMouseCaptured())
        associatedButton.SetColor(onClickColor);
    else
	    associatedButton.SetColor(onHoverColor);
}

void DefaultButtonBehavior::OnMouseLeft(EventMouseStateInfo e)
{
    associatedButton.SetColor(standardColor);
}

void DefaultButtonBehavior::OnMouseCaptured(EventMouseStateInfo e)
{

}

Vector3 DefaultButtonBehavior::GetStandardColor()
{
    return standardColor;
}

void DefaultButtonBehavior::SetStatelessColor(Vector3 statelessColor)
{
    DefaultButtonBehavior::standardColor = statelessColor;
}

Vector3 DefaultButtonBehavior::GetOnClickColor()
{
    return onClickColor;
}

Vector3 DefaultButtonBehavior::GetOnHoverColor()
{
    return onHoverColor;
}
