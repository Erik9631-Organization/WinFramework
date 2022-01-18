//
// Created by Erik on 1/18/2022.
//

#include "VerticalScrollbarBehavior.h"
#include "ScrollBar.h";
#include "Button.h";
#include "Adjustable.h"

VerticalScrollbarBehavior::VerticalScrollbarBehavior(ScrollBar &scrollbar, Button& button) :
        associatedScrollbar(scrollbar), associatedTrackBar(button)
{
    associatedTrackBar.AddMouseStateSubscriber(*this);
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
    float percentualPos = GetScrollbarPercentualPos();
    associatedTrackBar.SetY((int)percentualPos);
}

void VerticalScrollbarBehavior::SetPadding(int padding)
{
    this->padding = padding;
}

int VerticalScrollbarBehavior::GetPageHeight()
{
    Adjustable* lastComponent = GetLastComponent();
    if(lastComponent == nullptr)
        return 0;
    return lastComponent->GetY() + lastComponent->GetHeight();
}

Adjustable* VerticalScrollbarBehavior::GetLastComponent()
{
    Component* parent = associatedScrollbar.GetParent();
    if(parent == nullptr) // Not assigned to any container
        return nullptr;

    Adjustable* lastMovable = &parent->GetComponentNode().Get(0).GetValue();

    for(int i = 0; i < parent->GetComponentNode().GetNodeCount(); i++)
    {
        Adjustable& movable = parent->GetComponentNode().Get(i).GetValue();
        if(&movable == &associatedScrollbar)
            continue;
        if(movable.GetY() > lastMovable->GetY())
            lastMovable = &movable;
    }

    if(lastMovable == &associatedScrollbar)
        return nullptr;

    return lastMovable;
}

float VerticalScrollbarBehavior::GetScrollbarPercentualPos()
{
    return ( (float)associatedTrackBar.GetY() + (float)associatedTrackBar.GetHeight() ) / ( (float)associatedScrollbar.GetHeight() - (float)associatedTrackBar.GetHeight() );
}

float VerticalScrollbarBehavior::GetScrollbarPercentualHeight()
{
    int pageHeight = GetPageHeight();
    if(pageHeight == 0) // No scrollbar
        return 1.0f;
    return (float)associatedScrollbar.GetHeight() / (float)pageHeight;
}

void VerticalScrollbarBehavior::OnAdd(EventOnAddInfo<Component&> e)
{
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
        associatedTrackBar.SetColor(Color::Transparent);
        associatedTrackBar.SetActive(false);
        return;
    }
    associatedTrackBar.SetColor(associatedTrackBar.GetBackgroundColor());

    trackbarHeight = (float)associatedScrollbar.GetHeight() * scrollbarPercentualHeight;
    if(trackbarHeight < minSize) // Force minsize.
        trackbarHeight = minSize;

    associatedTrackBar.SetWidth(trackbarWidth);
    associatedTrackBar.SetHeight(trackbarHeight);

}

void VerticalScrollbarBehavior::OnResize(EventResizeInfo e)
{
    //Adjust scrollbar to the right side
    Gdiplus::Size size = e.GetSize();
    associatedScrollbar.SetPosition(size.Width - associatedScrollbar.GetWidth(), 0);
    associatedScrollbar.SetHeight(size.Height);

    UpdateThumbTrackSize();
}
