#include "DefaultResize.h"
#include "EventTypes/EventResizeInfo.h"
#include "Events/ResizeSubscriber.h"
#include "../GenericObj.h"
#include "vec2.hpp"

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

glm::vec2 DefaultResize::GetSize()
{
    return size;
}

float DefaultResize::GetWidth()
{
    return size.x;
}

float DefaultResize::GetHeight()
{
    return size.y;
}

void DefaultResize::SetSize(const glm::vec2 &size, bool emit)
{
    this->size = size;
    if(emit)
        NotifyOnResizeSubscribers(EventResizeInfo(size, &associatedResizable));
}

void DefaultResize::SetSize(float width, float height, bool emit)
{
    SetSize({width, height}, emit);
}

void DefaultResize::SetWidth(float width, bool emit)
{
    SetSize(width, size.GetY(), emit);
}

void DefaultResize::SetHeight(float height, bool emit)
{
    SetSize(size.GetX(), height, emit);
}

void DefaultResize::SetSize(Vector2 size)
{
    SetSize(size, true);
}

void DefaultResize::SetSize(float width, float height)
{
    SetSize(width, height, true);
}

void DefaultResize::SetWidth(float width)
{
    SetWidth(width, true);
}

void DefaultResize::SetHeight(float height)
{
    SetHeight(height, true);
}
