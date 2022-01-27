#include "EventResizeInfo.h"
#include "Components/UiElement.h"


Gdiplus::Size EventResizeInfo::GetSize()
{
	return this->size;
}

Resizable* EventResizeInfo::GetSrc()
{
	return src;
}


EventResizeInfo::EventResizeInfo(Gdiplus::Size size, Resizable* obj) : src(obj)
{
	this->size = size;
	this->src = src;
}

EventResizeInfo::~EventResizeInfo()
{
}
