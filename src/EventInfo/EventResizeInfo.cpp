#include "EventResizeInfo.h"
#include "Components/UiElement.h"


const glm::vec3 & EventResizeInfo::GetSize() const
{
	return this->size;
}

Resizable* EventResizeInfo::GetSrc() const
{
	return src;
}


EventResizeInfo::EventResizeInfo(glm::vec3 size, Resizable* src) : src(src)
{
	this->size = size;
	this->src = src;
}

EventResizeInfo::~EventResizeInfo()
{
}
