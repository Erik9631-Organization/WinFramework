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
    NotifyOnViewportReset(ViewportEventInfo(viewPortPosition, viewPortSize, this));
}

void DefaultViewport::SetViewportSize(const glm::vec3 &input)
{
    viewPortSize = input;
    NotifyOnViewportSizeChanged(ViewportEventInfo(viewPortPosition, input, this));
    isSet = true;
}

void DefaultViewport::SetViewportPosition(const glm::vec3 &input)
{
    viewPortPosition = input;
    NotifyOnViewportPositionChanged(ViewportEventInfo(input, viewPortSize, this));
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

void DefaultViewport::AddViewportSubscriber(ViewportSubscriber &subscriber)
{
    subscribers.push_back(&subscriber);
}

void DefaultViewport::RemoveViewportSubscriber(ViewportSubscriber &subscriber)
{
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), &subscriber), subscribers.end());
}

void DefaultViewport::NotifyOnViewportSizeChanged(const ViewportEventInfo &event)
{
    for (ViewportSubscriber* subscriber : subscribers)
        subscriber->OnViewportSizeChanged(event);
}

void DefaultViewport::NotifyOnViewportPositionChanged(const ViewportEventInfo &event)
{
    for (ViewportSubscriber* subscriber : subscribers)
        subscriber->OnViewportPositionChanged(event);
}

void DefaultViewport::NotifyOnViewportReset(const ViewportEventInfo &event)
{
    for (ViewportSubscriber* subscriber : subscribers)
        subscriber->OnViewportReset(event);
}
