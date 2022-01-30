#include "RenderEventInfo.h"

RenderEventInfo::RenderEventInfo(Renderer *renderer, Vector2 parentSize, Vector2 parentPosition)
{
	this->parentSize = parentSize;
	this->parentPosition = parentPosition;
    this->renderer = renderer;
}

RenderEventInfo::RenderEventInfo(Renderer *g) : RenderEventInfo(g, {0,0}, {0,0})
{
}

Renderer * RenderEventInfo::GetRenderer() const
{
	return renderer;
}

Vector2 RenderEventInfo::GetParentSize() const
{
	return parentSize;
}

void RenderEventInfo::SetParentSize(Vector2 parentSize)
{
	this->parentSize = parentSize;
}


Vector2 RenderEventInfo::GetParentPosition() const
{
    return parentPosition;
}
