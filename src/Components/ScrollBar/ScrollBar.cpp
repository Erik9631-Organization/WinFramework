//
// Created by Erik on 1/18/2022.
//

#include "ScrollBar.h"
#include "MouseStateSubscriber.h"

ScrollBar::ScrollBar(int x, int y, int width, int height, const string &name) :
        Panel(x, y, width, height, name),
        thumbTrack(0, 0, 0, 0),
        scrollbarBehavior(*this, thumbTrack)
{
    Add(thumbTrack);
}

ScrollBar::ScrollBar(const string &name) :
        ScrollBar(0, 0, 0, 0, name)
{

}

ScrollBar::ScrollBar() :
        ScrollBar(0, 0, 0, 0, "")
{

}

void ScrollBar::Control(UiElement* component)
{
    if(controlledComponent != nullptr)
        ClearControl();

    //For every child in the component
    //Remove it from the parent
    //Add it to the scrollPane


    //If control is lost
    //Reassign the components to the parent

    controlledComponent = component;
    controlledComponent->Add(*this);

    controlledComponent->AddOnResizeSubscriber(scrollbarBehavior);
    controlledComponent->AddOnAddSubscriber(scrollbarBehavior);

    //Send resize event to calculate the position
    EventResizeInfo resizeInfo = EventResizeInfo(controlledComponent->GetSize(), controlledComponent);
    scrollbarBehavior.OnResize(resizeInfo);
}

void ScrollBar::ClearControl()
{
    controlledComponent->RemoveOnResizeSubscriber(scrollbarBehavior);
    controlledComponent->RemoveOnAddSubscriber(scrollbarBehavior);
    controlledComponent = nullptr;
}

UiElement *ScrollBar::GetControlledComponent()
{
    return controlledComponent;
}
