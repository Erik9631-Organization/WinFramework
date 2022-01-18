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

void ScrollBar::Control(Component* component)
{
    if(controlledComponent != nullptr)
        ClearControl();

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
