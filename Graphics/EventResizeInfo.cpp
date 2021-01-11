#include "EventResizeInfo.h"
#include "Component.h"


Gdiplus::Size EventResizeInfo::GetSize()
{
	return this->size;
}


EventResizeInfo::EventResizeInfo(Gdiplus::Size size)
{
	this->size = size;
}


EventResizeInfo::~EventResizeInfo()
{
}
