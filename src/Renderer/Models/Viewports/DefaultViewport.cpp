//
// Created by erik9 on 1/17/2023.
//

#include "DefaultViewport.h"

bool DefaultViewport::IsViewportSet() const
{
    return isSet;
}

void DefaultViewport::ResetViewport()
{
    this->isSet = false;
    NotifyOnViewportReset(Viewport2EventInfo(viewPortPosition, viewPortSize, this));
}

void DefaultViewport::SetViewportSize(const glm::vec3 &input)
{
    viewPortSize = input;
    NotifyOnViewportSizeChanged(Viewport2EventInfo(viewPortPosition, input, this));
    isSet = true;
}

void DefaultViewport::SetViewportPosition(const glm::vec3 &input)
{
    viewPortPosition = input;
    NotifyOnViewportPositionChanged(Viewport2EventInfo(input, viewPortSize, this));
    isSet = true;
}

const glm::vec3 & DefaultViewport::GetViewportSize()
{
    return viewPortSize;
}

const glm::vec3 & DefaultViewport::GetViewportPosition()
{
    return viewPortPosition;
}

void DefaultViewport::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    subscribers.push_back(&subscriber);
}

void DefaultViewport::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), &subscriber), subscribers.end());
}

void DefaultViewport::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    for (Viewport2Subscriber* subscriber : subscribers)
        subscriber->OnViewportSizeChanged(event);
}

void DefaultViewport::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    for (Viewport2Subscriber* subscriber : subscribers)
        subscriber->OnViewportPositionChanged(event);
}

void DefaultViewport::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    for (Viewport2Subscriber* subscriber : subscribers)
        subscriber->OnViewportReset(event);
}
