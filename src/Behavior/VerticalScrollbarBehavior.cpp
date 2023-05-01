//
// Created by Erik on 1/18/2022.
//

#include <execution>
#include "VerticalScrollbarBehavior.h"
#include "ScrollBar.h"
#include "Button.h"
#include "Adjustable.h"
using namespace std;

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
    //Set viewPortSize
    //Check if scrollbar can be moved
    if(e.GetMouseDelta().y + associatedTrackBar.GetPosition().y + associatedTrackBar.GetSize().y > associatedScrollbar.GetControlledComponent()->GetSize().y)
        return;

    if(e.GetMouseDelta().y + associatedTrackBar.GetPosition().y < 0)
        return;
    //Set the trackbar
    auto pos = associatedTrackBar.GetPosition();
    pos.y = e.GetMouseDelta().y + associatedTrackBar.GetPosition().y;
    associatedTrackBar.SetPosition(pos);

    //Set the components
    UiElement* parent = associatedScrollbar.GetParent();
    float percentualPos = GetScrollbarPercentualPos();
    float pageHeight = GetPageHeight();
    //We only want the offset of the not visible part, not the complete page offset
    //pageHeight includes the offset and the window viewPortPosition itself. If we move the scrollbar, we want to apply only the offset
    //That is why we need to subtract
    float offset = (percentualPos * (pageHeight - associatedScrollbar.GetControlledComponent()->GetSize().y));

    parent->SetChildrenTranslate({0, -offset, 0, 0});
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
    return bottomComponent->GetPosition().y + bottomComponent->GetSize().y;
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

        if(movable.GetPosition().y> lastMovable->GetPosition().y)
            lastMovable = &movable;
    }

    if(lastMovable == &associatedScrollbar)
        return nullptr;

    return lastMovable;
}

float VerticalScrollbarBehavior::GetScrollbarPercentualPos()
{
    return (float)associatedTrackBar.GetPosition().y / ((float)associatedScrollbar.GetSize().y - (float)associatedTrackBar.GetSize().y);
}

float VerticalScrollbarBehavior::GetScrollbarPercentualHeight()
{
    int pageHeight = GetPageHeight();
    if(pageHeight == 0) // No scrollbar
        return 1.0f;
    return (float)associatedScrollbar.GetControlledComponent()->GetSize().y / (float)pageHeight;
}

void VerticalScrollbarBehavior::OnAdd(EventOnAddInfo<unique_ptr<UiElement>> e)
{
    //Subscribe to added component in order to keep track of move and resize
    e.GetAddedComponent()->get()->AddOnResizeSubscriber(*this);
    e.GetAddedComponent()->get()->AddOnMoveSubscriber(*this);
    auto* addedComponent = e.GetAddedComponent()->get();
    addedComponent->SetViewportSize(associatedScrollbar.GetControlledComponent()->GetSize());
    addedComponent->SetViewportPosition(associatedScrollbar.GetControlledComponent()->GetPosition());

    if(bottomComponent == nullptr)
        bottomComponent = GetBottomComponentFromParent();
    else
        bottomComponent = GetBottomComponent(e.GetAddedComponent()->get());
    UpdateThumbTrackSize();
}

void VerticalScrollbarBehavior::UpdateThumbTrackSize()
{
    int trackbarWidth = associatedScrollbar.GetSize().x - padding;
    int trackbarHeight = minSize;
    float scrollbarPercentualHeight = GetScrollbarPercentualHeight();

    //Set width and height
    if(scrollbarPercentualHeight >= 1.0f)
    {
        associatedTrackBar.SetBackgroundColor({255, 255, 255, 255});
        associatedTrackBar.SetActive(false);
        return;
    }
    associatedTrackBar.SetBackgroundColor({30, 30, 30, 255});

    trackbarHeight = (float)associatedScrollbar.GetControlledComponent()->GetSize().x * scrollbarPercentualHeight;
    if(trackbarHeight < minSize) // Force minsize.
        trackbarHeight = minSize;

    auto size = associatedScrollbar.GetSize();
    size.x = trackbarWidth;
    size.y = trackbarHeight;
    associatedTrackBar.SetSize(size);
}

void VerticalScrollbarBehavior::OnResize(EventResizeInfo e)
{
    //Adjust scrollbar to the right side
    auto* resizable = dynamic_cast<Resizable*>(e.GetSource());


    if(resizable == associatedScrollbar.GetControlledComponent())
    {
        auto scrollbarPos = this->associatedScrollbar.GetPosition();
        associatedScrollbar.SetPosition({e.GetSize().x - associatedScrollbar.GetSize().x, 0, scrollbarPos.z});
        auto scrollbarSize = associatedScrollbar.GetSize();
        scrollbarSize.y = e.GetSize().y;
        associatedScrollbar.SetSize(scrollbarSize);
        UpdateChildrenViewports(*associatedScrollbar.GetControlledComponent());
    }
    else
    {
        if(e.GetSource() == nullptr)
            return;
        bottomComponent = GetBottomComponent(dynamic_cast<Adjustable*>(e.GetSource()));
    }

    UpdateThumbTrackSize();
}

void VerticalScrollbarBehavior::OnMove(EventMoveInfo e)
{
    auto * src = dynamic_cast<Adjustable*>(e.GetSource());
    if(src == nullptr)
        return;
    if(e.GetSource() == static_cast<Adjustable*>(associatedScrollbar.GetControlledComponent()))
    {
        UpdateChildrenViewports(*associatedScrollbar.GetControlledComponent());
    }
    bottomComponent = GetBottomComponent(src);
}

Adjustable *VerticalScrollbarBehavior::GetBottomComponent(Adjustable *adjustable)
{
    if(adjustable == nullptr)
        return bottomComponent;
    if(bottomComponent == nullptr)
        return nullptr;

    if(adjustable->GetPosition().y + adjustable->GetSize().y > bottomComponent->GetPosition().y + bottomComponent->GetSize().y)
        return adjustable;
    return bottomComponent;
}

void VerticalScrollbarBehavior::UpdateChildrenViewports(UiElement &root)
{
    auto controlledComponent = this->associatedScrollbar.GetControlledComponent();
    if(controlledComponent == nullptr)
        return;
    std::for_each(std::execution::par, root.GetUiElementNode().GetNodes().begin(), root.GetUiElementNode().GetNodes().end(), [&](std::unique_ptr<MultiTree<std::unique_ptr<UiElement>>>& child)
    {
        child->GetValue()->SetViewportSize(controlledComponent->GetSize());
        child->GetValue()->SetViewportPosition(controlledComponent->GetPosition());
        UpdateChildrenViewports(*child->GetValue());
    });
}
