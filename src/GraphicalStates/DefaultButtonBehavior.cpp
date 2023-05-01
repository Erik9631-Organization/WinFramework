#include "EventMouseStateInfo.h"
#include "Button.h"
#include <iostream>

DefaultButtonBehavior::DefaultButtonBehavior(Button& button) : associatedButton(button)
{
	associatedButton.AddMouseStateSubscriber(*this);
    associatedButton.SetBackgroundColor(backgroundColor);
}

void DefaultButtonBehavior::SetOnHoverBackgroundColor(const glm::ivec4 &color)
{
    onHoverBackgroundColor = color;
}

void DefaultButtonBehavior::SetOnClickBackgroundColor(const glm::ivec4 &color)
{
    onClickBackgroundColor = color;
}


void DefaultButtonBehavior::OnMouseDown(EventMouseStateInfo e)
{
    associatedButton.SetBackgroundColor(onClickBackgroundColor);
}

void DefaultButtonBehavior::OnMouseUp(EventMouseStateInfo e)
{
    if(associatedButton.HasMouseEntered())
        associatedButton.SetBackgroundColor(onHoverBackgroundColor);
    else
        associatedButton.SetBackgroundColor(backgroundColor);
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
        associatedButton.SetBackgroundColor(onClickBackgroundColor);
    else
        associatedButton.SetBackgroundColor(onHoverBackgroundColor);
}

void DefaultButtonBehavior::OnMouseLeft(EventMouseStateInfo e)
{
    associatedButton.SetBackgroundColor(backgroundColor);
}

void DefaultButtonBehavior::OnMouseCaptured(EventMouseStateInfo e)
{

}

const glm::ivec4 & DefaultButtonBehavior::GetStandardColor()
{
    return backgroundColor;
}

void DefaultButtonBehavior::SetBackgroundColor(const glm::ivec4 &statelessColor)
{
    backgroundColor = statelessColor;
    associatedButton.SetBackgroundColor(backgroundColor);
}

const glm::ivec4 & DefaultButtonBehavior::GetOnClickColor()
{
    return onClickBackgroundColor;
}

const glm::ivec4 & DefaultButtonBehavior::GetOnHoverColor()
{
    return onHoverBackgroundColor;
}
