//
// Created by erik9 on 5/14/2023.
//

#include "EventCoreLifecycleInfo.h"
#include "Core.h"

EventSource *EventCoreLifecycleInfo::GetSource() const
{
    return core;
}

Core *EventCoreLifecycleInfo::GetCore() const
{
    return core;
}

EventCoreLifecycleInfo::EventCoreLifecycleInfo(Core *core, EventSource *source)
{
    this->core = core;
    this->src = source;
}
