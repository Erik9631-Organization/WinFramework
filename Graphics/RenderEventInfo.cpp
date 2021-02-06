#include "RenderEventInfo.h"

RenderEventInfo::RenderEventInfo(Gdiplus::Graphics* g)
{
	graphics = g;
}

Gdiplus::Graphics* RenderEventInfo::GetGraphics()
{
	return graphics;
}
