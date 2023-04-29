//
// Created by erik9 on 12/12/2022.
//

#include "ResizableModelBehavior.h"

const glm::vec4 & ResizableModelBehavior::GetSize() const
{
    return size;
}

void ResizableModelBehavior::SetSize(const glm::vec4 &size, bool emit)
{
    this->size = size;
}

void ResizableModelBehavior::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    for(auto* subscriber : resizeSubscribers)
        subscriber->OnResize(event);
}

void ResizableModelBehavior::AddOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizeSubscribers.push_back(&subscriber);
}

void ResizableModelBehavior::RemoveOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    for(auto it = resizeSubscribers.begin(); it != resizeSubscribers.end(); it++)
    {
        if(*it == &subscriber)
        {
            resizeSubscribers.erase(it);
            return;
        }
    }
}
