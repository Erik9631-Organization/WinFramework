//
// Created by Erik on 20/03/22.
//

#include "RenderObjectEventInfo.h"
#include "RenderObjectSubscriber.h"

RenderObjectEventInfo::RenderObjectEventInfo(std::any src, std::any eventData)
{
    this->src = src;
    this->eventData = eventData;
}

