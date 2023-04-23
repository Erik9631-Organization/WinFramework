//
// Created by erik9 on 1/17/2023.
//

#include "DefaultViewport2.h"

bool DefaultViewport2::IsViewportSet() const
{
    return isSet;
}

void DefaultViewport2::ResetViewport()
{
    this->isSet = false;
}

void DefaultViewport2::SetViewportSize(const glm::vec4 &vec4)
{
    viewPortSize = vec4;
    NotifyOnViewportSizeChanged(Viewport2EventInfo(viewPortPosition, viewPortSize, this));
    isSet = true;
}

void DefaultViewport2::SetViewportPosition(const glm::vec4 &vec4)
{
    viewPortPosition = vec4;
    NotifyOnViewportPositionChanged(Viewport2EventInfo(viewPortPosition, viewPortSize, this));
    isSet = true;
}

glm::vec4 & DefaultViewport2::GetViewportSize()
{
    return viewPortSize;
}

glm::vec4 & DefaultViewport2::GetViewportPosition()
{
    return viewPortPosition;
}

void DefaultViewport2::AddViewport2Subscriber(Viewport2Subscriber *subscriber)
{
    subscribers.push_back(subscriber);
}

void DefaultViewport2::RemoveViewport2Subscriber(Viewport2Subscriber *subscriber)
{
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
}

void DefaultViewport2::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    for (Viewport2Subscriber* subscriber : subscribers)
        subscriber->OnViewportSizeChanged(event);
}

void DefaultViewport2::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    for (Viewport2Subscriber* subscriber : subscribers)
        subscriber->OnViewportPositionChanged(event);
}
