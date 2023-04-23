#include "DefaultResize.h"
#include "EventResizeInfo.h"
#include "ResizeSubscriber.h"
#include "GenericObj.h"

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

const glm::vec4 & DefaultResize::GetSize()
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

void DefaultResize::SetSize(const glm::vec4 &size, bool emit)
{
    this->size = size;
    if(emit)
        NotifyOnResizeSubscribers(EventResizeInfo(size, &associatedResizable));
}

void DefaultResize::SetSize(float width, float height, bool emit)
{
    SetSize({width, height, 0, 0}, emit);
}

void DefaultResize::SetWidth(float width, bool emit)
{
    SetSize(width, size.y, emit);
}

void DefaultResize::SetHeight(float height, bool emit)
{
    SetSize(size.x, height, emit);
}

void DefaultResize::SetSize(glm::vec4 size)
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
