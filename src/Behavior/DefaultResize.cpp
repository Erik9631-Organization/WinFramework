#include "DefaultResize.h"
#include "EventTypes/EventResizeInfo.h"
#include "Events/ResizeSubscriber.h"
#include "../GenericObj.h"

DefaultResize::DefaultResize(Resizable& resizeComponent) : associatedResizable(resizeComponent)
{
}

void DefaultResize::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    for (ResizeSubscriber& resizable : subscribers)
        resizable.OnResize(event);
}

void DefaultResize::AddOnResizeSubscriber(ResizeSubscriber& subscriber)
{
    //CRASH1
    subscribers.push_back(subscriber);
}

void DefaultResize::RemoveOnResizeSubscriber(ResizeSubscriber& subscriber)
{
    for (std::vector<std::reference_wrapper<ResizeSubscriber>>::iterator i = subscribers.begin(); i != subscribers.end(); i++)
    {
        if (&subscriber == &i->get())
            return;
    }
}

Vector2 DefaultResize::GetSize()
{
    return size;
}

float DefaultResize::GetWidth()
{
    return size.GetX();
}

float DefaultResize::GetHeight()
{
    return size.GetY();
}

void DefaultResize::SetSize(Vector2 size, bool emit)
{
    this->size = size;
    NotifyOnResizeSubscribers(EventResizeInfo(size, &associatedResizable));
}

void DefaultResize::SetSize(float width, float height, bool emit)
{
    SetSize({width, height}, false);
}

void DefaultResize::SetWidth(float width)
{
    SetSize(width, size.GetY(), false);
}

void DefaultResize::SetHeight(float height)
{
    SetSize(size.GetX(), height, false);
}
