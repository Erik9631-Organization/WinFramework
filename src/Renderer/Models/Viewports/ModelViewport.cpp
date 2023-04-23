//
// Created by erik9 on 1/17/2023.
//

#include "ModelViewport.h"

bool ModelViewport::IsViewportSet() const
{
    return isSet;
}

void ModelViewport::ResetViewport()
{
    this->isSet = false;
    NotifyOnViewportReset(Viewport2EventInfo(viewPortPosition, viewPortSize, this));
}

void ModelViewport::SetViewportSize(const glm::vec4 &vec4)
{
    viewPortSize = vec4;
    NotifyOnViewportSizeChanged(Viewport2EventInfo(viewPortPosition, vec4, this));
    isSet = true;
}

void ModelViewport::SetViewportPosition(const glm::vec4 &vec4)
{
    viewPortPosition = vec4;
    NotifyOnViewportPositionChanged(Viewport2EventInfo(vec4, viewPortSize, this));
    isSet = true;
}

glm::vec4 & ModelViewport::GetViewportSize()
{
    return viewPortSize;
}

glm::vec4 & ModelViewport::GetViewportPosition()
{
    return viewPortPosition;
}

void ModelViewport::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    subscribers.push_back(&subscriber);
}

void ModelViewport::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), &subscriber), subscribers.end());
}

void ModelViewport::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    for (Viewport2Subscriber* subscriber : subscribers)
        subscriber->OnViewportSizeChanged(event);
}

void ModelViewport::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    for (Viewport2Subscriber* subscriber : subscribers)
        subscriber->OnViewportPositionChanged(event);
}

void ModelViewport::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    for (Viewport2Subscriber* subscriber : subscribers)
        subscriber->OnViewportReset(event);
}
