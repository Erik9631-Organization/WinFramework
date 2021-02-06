#include "DefaultResize.h"
#include "EventResizeInfo.h"
#include "ResizeSubscriber.h"

void DefaultResize::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    for (ResizeSubscriber& resizable : subscribers)
        resizable.OnResize(event);
}

void DefaultResize::AddOnResizeSubscriber(ResizeSubscriber& subscriber)
{
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

Gdiplus::Size DefaultResize::GetSize()
{
    return size;
}

int DefaultResize::GetWidth()
{
    return size.Width;
}

int DefaultResize::GetHeight()
{
    return size.Height;
}

void DefaultResize::SetSize(Gdiplus::Size size)
{
    this->size = size;
}

void DefaultResize::SetSize(int width, int height)
{
    this->size = Gdiplus::Size(width, height);
}

void DefaultResize::SetWidth(int width)
{
    SetSize(width, size.Height);
}

void DefaultResize::SetHeight(int height)
{
    SetSize(size.Width, height);
}
