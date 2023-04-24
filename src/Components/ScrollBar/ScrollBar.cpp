//
// Created by Erik on 1/18/2022.
//

#include "ScrollBar.h"
#include "MouseStateSubscriber.h"
using namespace std;

ScrollBar::ScrollBar(int x, int y, int width, int height, const string &name) :
        Panel(x, y, width, height, name)
{
    thumbTrack = new Button(0.0f, 0.0f, 0.0f, 0.0f, "thumbTrackButton");
    scrollbarBehavior = std::make_unique<VerticalScrollbarBehavior>(*this, *thumbTrack);
    Add(std::unique_ptr<Button>(thumbTrack));
}

ScrollBar::ScrollBar(const string &name) :
        ScrollBar(0, 0, 0, 0, name)
{

}

ScrollBar::ScrollBar() :
        ScrollBar(0, 0, 0, 0, "")
{

}

void ScrollBar::Control(UiElement &component, std::unique_ptr<ScrollBar> scrollbar)
{
    auto& scrollbarRef = *scrollbar;
    if(scrollbar->controlledComponent != nullptr)
        scrollbar->ClearControl();

    //For every child in the component
    //Remove it from the parent
    //Add it to the scrollPane


    //If control is lost
    //Reassign the components to the parent

    scrollbar->controlledComponent = &component;
    component.Add(std::move(scrollbar));

    component.AddOnResizeSubscriber(*scrollbarRef.scrollbarBehavior);
    component.AddOnMoveSubscriber(*scrollbarRef.scrollbarBehavior);
    component.AddOnAddSubscriber(*scrollbarRef.scrollbarBehavior);

    //Send resize event to calculate the viewPortSize
    EventResizeInfo resizeInfo = EventResizeInfo(component.GetSize(), &component);
    scrollbarRef.scrollbarBehavior->OnResize(resizeInfo);
}

void ScrollBar::ClearControl()
{
    controlledComponent->RemoveOnResizeSubscriber(*scrollbarBehavior);
    controlledComponent->RemoveOnAddSubscriber(*scrollbarBehavior);
    controlledComponent = nullptr;
}

UiElement *ScrollBar::GetControlledComponent()
{
    return controlledComponent;
}
