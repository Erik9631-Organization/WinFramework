#include "RenderEventInfo.h"
#include "CoreWindow.h"
#include "RenderingPool.h"

RenderingPool * RenderEventInfo::GetRenderer() const
{
    return renderer;
}


RenderEventInfo::RenderEventInfo(RenderingPool *g)
{
    this->renderer = g;
}
