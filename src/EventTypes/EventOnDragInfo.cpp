#include "EventOnDragInfo.h"

EventOnDragInfo::EventOnDragInfo(Draggable& src) : src(src)
{

}

Draggable& EventOnDragInfo::GetSrc()
{
	return src;
}
