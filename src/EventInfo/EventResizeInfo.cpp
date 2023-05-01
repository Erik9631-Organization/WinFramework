#include "EventResizeInfo.h"
#include "Components/UiElement.h"


const glm::vec3 & EventResizeInfo::GetSize() const
{
	return this->size;
}


EventResizeInfo::EventResizeInfo(glm::vec3 size, EventSource *src) : src(src)
{
	this->size = size;
	this->src = src;
}

EventSource * EventResizeInfo::GetSource() const
{
    return src;
}
