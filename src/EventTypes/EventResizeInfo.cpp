#include "EventResizeInfo.h"
#include "Components/UiElement.h"


Vector2 EventResizeInfo::GetSize() const
{
	return this->size;
}

Resizable* EventResizeInfo::GetSrc() const
{
	return src;
}


EventResizeInfo::EventResizeInfo(Vector2 size, Resizable* src) : src(src)
{
	this->size = size;
	this->src = src;
}

EventResizeInfo::~EventResizeInfo()
{
}
