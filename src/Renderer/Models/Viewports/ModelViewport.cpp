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

void ModelViewport::SetViewportSize(const glm::vec3 &input)
{
    viewPortSize = input;
    NotifyOnViewportSizeChanged(Viewport2EventInfo(viewPortPosition, input, this));
    isSet = true;
}

void ModelViewport::SetViewportPosition(const glm::vec3 &input)
{
    viewPortPosition = input;
    NotifyOnViewportPositionChanged(Viewport2EventInfo(input, viewPortSize, this));
    isSet = true;
}

const glm::vec3 & ModelViewport::GetViewportSize()
{
    return viewPortSize;
}

const glm::vec3 & ModelViewport::GetViewportPosition()
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
