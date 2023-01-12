#include "EventResizeInfo.h"
#include "Components/UiElement.h"


glm::vec4 EventResizeInfo::GetSize() const
{
	return this->size;
}

Resizable* EventResizeInfo::GetSrc() const
{
	return src;
}


EventResizeInfo::EventResizeInfo(glm::vec4 size, Resizable* src) : src(src)
{
	this->size = size;
	this->src = src;
}

EventResizeInfo::~EventResizeInfo()
{
}
