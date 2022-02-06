#include "RenderEventInfo.h"

RenderEventInfo::RenderEventInfo(Renderer *renderer)
{
    this->renderer = renderer;
}

Renderer * RenderEventInfo::GetRenderer() const
{
    return renderer;
}
