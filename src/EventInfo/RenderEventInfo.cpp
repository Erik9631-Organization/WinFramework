#include "RenderEventInfo.h"
#include "WindowsCore.h"
#include "RenderingPool.h"

RenderingPool * RenderEventInfo::GetRenderer() const
{
    return renderer;
}


RenderEventInfo::RenderEventInfo(RenderingPool *g, EventSource *source)
{
    this->renderer = g;
    this->source = source;
}

EventSource * RenderEventInfo::GetSource() const
{
    return source;
}
