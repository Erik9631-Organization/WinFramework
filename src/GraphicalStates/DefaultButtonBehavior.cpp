#include "EventTypes/EventMouseStateInfo.h"
#include "Components/Button.h"
DefaultButtonBehavior::DefaultButtonBehavior(Button& button) : associatedButton(button)
{
	associatedButton.AddMouseStateSubscriber(*this);
	onHoverColor = Color::MakeARGB(255, 100, 100, 100);
	onClickColor = Color::MakeARGB(255, 60, 60, 60);
}

void DefaultButtonBehavior::SetOnHoverColor(Gdiplus::Color color)
{
	onHoverColor = color;
}

void DefaultButtonBehavior::SetOnClickColor(Gdiplus::Color color)
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

Color DefaultButtonBehavior::GetStandardColor()
{
    return standardColor;
}

void DefaultButtonBehavior::SetStatelessColor(Color statelessColor)
{
    DefaultButtonBehavior::standardColor = statelessColor;
}

Color DefaultButtonBehavior::GetOnClickColor()
{
    return onClickColor;
}

Color DefaultButtonBehavior::GetOnHoverColor()
{
    return onHoverColor;
}
