//
// Created by Erik on 20/03/22.
//

#include "RenderObjectEventInfo.h"

#include <utility>
#include "RenderObjectSubscriber.h"

RenderObjectEventInfo::RenderObjectEventInfo(EventSource *src, std::any eventData)
{
    this->eventData = std::move(eventData);
    this->src = src;
}

EventSource * RenderObjectEventInfo::GetSource() const
{
    return src;
}

