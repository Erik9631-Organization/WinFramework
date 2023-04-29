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

const glm::vec4 & DefaultResize::GetSize() const
{
    return size;
}

void DefaultResize::SetSize(const glm::vec4 &size, bool emit)
{
    this->size = size;
    if(emit)
        NotifyOnResizeSubscribers(EventResizeInfo(size, &associatedResizable));
}