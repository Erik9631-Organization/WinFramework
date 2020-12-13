#include "EventResizeInfo.h"
#include "Component.h"


Gdiplus::Size EventResizeInfo::GetSize()
{
	return component.GetSize();
}

Gdiplus::Size EventResizeInfo::GetRelativeSize()
{
	return component.GetSize() - oldSize;
}

EventResizeInfo::EventResizeInfo(Component & component) : EventInfo(component)
{

}


EventResizeInfo::~EventResizeInfo()
{
}
