//
// Created by erik9 on 12/12/2022.
//

#include "ResizableModelBehavior.h"

const glm::vec4 & ResizableModelBehavior::GetSize()
{
    return size;
}

float ResizableModelBehavior::GetWidth()
{
    return size.x;
}

float ResizableModelBehavior::GetHeight()
{
    return size.y;
}

void ResizableModelBehavior::SetSize(const glm::vec4 &size, bool emit)
{
    this->size = size;
}

void ResizableModelBehavior::SetSize(glm::vec4 size)
{
    SetSize(size, false);
}

void ResizableModelBehavior::SetSize(float width, float height, bool emit)
{
    SetSize({width, height, 0, 0}, emit);
}

void ResizableModelBehavior::SetSize(float width, float height)
{
    SetSize({width, height, 0, 0});
}

void ResizableModelBehavior::SetWidth(float width, bool emit)
{
    SetSize({width, size.y, 0, 0}, emit);
}

void ResizableModelBehavior::SetWidth(float width)
{
    SetWidth(width, false);
}

void ResizableModelBehavior::SetHeight(float height, bool emit)
{
    SetSize({size.x, height, 0, 0}, emit);
}

void ResizableModelBehavior::SetHeight(float height)
{
    SetHeight(height, false);
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
