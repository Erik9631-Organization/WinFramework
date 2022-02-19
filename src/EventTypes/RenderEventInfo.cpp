#include "RenderEventInfo.h"
#include "CoreWindow.h"

RenderEventInfo::RenderEventInfo(Renderer *renderer)
{
    this->renderer = renderer;
}

Renderer * RenderEventInfo::GetRenderer() const
{
    return renderer;
}