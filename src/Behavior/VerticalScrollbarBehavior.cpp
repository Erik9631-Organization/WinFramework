//
// Created by Erik on 1/18/2022.
//

#include "VerticalScrollbarBehavior.h"
#include "ScrollBar.h"
#include "Button.h"
#include "api/Adjustable.h"

VerticalScrollbarBehavior::VerticalScrollbarBehavior(ScrollBar &scrollbar, Button& button) :
        associatedScrollbar(scrollbar), associatedTrackBar(button)
{
    associatedTrackBar.AddMouseStateSubscriber(*this);
    associatedScrollbar.SetIgnoreTranslate(true);
}

void VerticalScrollbarBehavior::OnMouseDown(EventMouseStateInfo e)
{

}

void VerticalScrollbarBehavior::OnMouseUp(EventMouseStateInfo e)
{

}

void VerticalScrollbarBehavior::OnMousePressed(EventMouseStateInfo e)
{

}

void VerticalScrollbarBehavior::OnMouseMove(EventMouseStateInfo e)
{

}

void VerticalScrollbarBehavior::OnMouseEntered(EventMouseStateInfo e)
{

}

void VerticalScrollbarBehavior::OnMouseLeft(EventMouseStateInfo e)
{

}

void VerticalScrollbarBehavior::OnMouseCaptured(EventMouseStateInfo e)
{
    //Set position
    //Check if scrollbar can be moved
    if(e.GetMouseDelta().y + associatedTrackBar.GetY() + associatedTrackBar.GetHeight() > associatedScrollbar.GetControlledComponent()->GetHeight())
        return;

    if(e.GetMouseDelta().y + associatedTrackBar.GetY() < 0)
        return;
    //Set the trackbar
    associatedTrackBar.SetY(e.GetMouseDelta().y + associatedTrackBar.GetY());

    //Set the components
    UiElement* parent = associatedScrollbar.GetParent();
    float percentualPos = GetScrollbarPercentualPos();
    float pageHeight = GetPageHeight();
    //We only want the offset of the not visible part, not the complete page offset
    //pageHeight includes the offset and the window size itself. If we move the scrollbar, we want to apply only the offset
    //That is why we need to subtract
    float offset = (percentualPos * (pageHeight - associatedScrollbar.GetControlledComponent()->GetHeight()));

    parent->SetChildrenTranslate({0, -offset});
}

void VerticalScrollbarBehavior::SetPadding(int padding)
{
    this->padding = padding;
}

int VerticalScrollbarBehavior::GetPageHeight()
{
    if(bottomComponent == nullptr)
        return 0;

    if(associatedScrollbar.GetControlledComponent() == nullptr)
        return 0;
    return bottomComponent->GetY() + bottomComponent->GetHeight();
}

Adjustable* VerticalScrollbarBehavior::GetBottomComponentFromParent()
{
    UiElement* controlledComponent = associatedScrollbar.GetControlledComponent();
    if(controlledComponent == nullptr) // Not assigned to any container
        return nullptr;

    Adjustable* lastMovable = controlledComponent->GetUiElementNode().Get(0).get();

    for(int i = 0; i < controlledComponent->GetUiElementNode().GetNodeCount(); i++)
    {
        Adjustable& movable = *controlledComponent->GetUiElementNode().Get(i);
        if(&movable == &associatedScrollbar)
            continue;

        if(lastMovable == &associatedScrollbar)
            lastMovable = &movable;

        if(movable.GetY() > lastMovable->GetY())
            lastMovable = &movable;
    }

    if(lastMovable == &associatedScrollbar)
        return nullptr;

    return lastMovable;
}

float VerticalScrollbarBehavior::GetScrollbarPercentualPos()
{
    return (float)associatedTrackBar.GetY() / ((float)associatedScrollbar.GetHeight() - (float)associatedTrackBar.GetHeight());
}

float VerticalScrollbarBehavior::GetScrollbarPercentualHeight()
{
    int pageHeight = GetPageHeight();
    if(pageHeight == 0) // No scrollbar
        return 1.0f;
    return (float)associatedScrollbar.GetControlledComponent()->GetHeight() / (float)pageHeight;
}

void VerticalScrollbarBehavior::OnAdd(EventOnAddInfo<unique_ptr<UiElement>> e)
{
    //Subscribe to added component in order to keep track of move and resize
    e.GetAddedComponent()->get()->AddOnResizeSubscriber(*this);
    e.GetAddedComponent()->get()->AddOnMoveSubscriber(*this);

    if(bottomComponent == nullptr)
        bottomComponent = GetBottomComponentFromParent();
    else
        bottomComponent = GetBottomComponent(e.GetAddedComponent()->get());
    UpdateThumbTrackSize();
}

void VerticalScrollbarBehavior::UpdateThumbTrackSize()
{
    int trackbarWidth = associatedScrollbar.GetWidth() - padding;
    int trackbarHeight = minSize;
    float scrollbarPercentualHeight = GetScrollbarPercentualHeight();

    //Set width and height
    if(scrollbarPercentualHeight >= 1.0f)
    {
        associatedTrackBar.SetColor({255, 255, 255});
        associatedTrackBar.SetActive(false);
        return;
    }
    associatedTrackBar.SetColor(associatedTrackBar.GetBackgroundColor());

    trackbarHeight = (float)associatedScrollbar.GetControlledComponent()->GetHeight() * scrollbarPercentualHeight;
    if(trackbarHeight < minSize) // Force minsize.
        trackbarHeight = minSize;

    associatedTrackBar.SetWidth(trackbarWidth);
    associatedTrackBar.SetHeight(trackbarHeight);

}

void VerticalScrollbarBehavior::OnResize(EventResizeInfo e)
{
    //Adjust scrollbar to the right side


    if(e.GetSrc() == associatedScrollbar.GetControlledComponent())
    {
        associatedScrollbar.SetPosition(e.GetSize().x - associatedScrollbar.GetWidth(), 0);
        associatedScrollbar.SetHeight(e.GetSize().y);
    }
    else
    {
        if(e.GetSrc() == nullptr)
            return;
        bottomComponent = GetBottomComponent(dynamic_cast<Adjustable*>(e.GetSrc()));
    }


    UpdateThumbTrackSize();
}

void VerticalScrollbarBehavior::OnMove(EventMoveInfo e)
{
    Adjustable* src = dynamic_cast<Adjustable*>(e.GetSrc());
    if(src == nullptr)
        return;
    bottomComponent = GetBottomComponent(src);
}

Adjustable *VerticalScrollbarBehavior::GetBottomComponent(Adjustable *adjustable)
{
    if(adjustable == nullptr)
        return bottomComponent;
    if(bottomComponent == nullptr)
        return nullptr;

    if(adjustable->GetY() + adjustable->GetHeight() > bottomComponent->GetY() + bottomComponent->GetHeight())
        return adjustable;
    return bottomComponent;
}
