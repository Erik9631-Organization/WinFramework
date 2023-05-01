#include "EventOnDragInfo.h"

EventOnDragInfo::EventOnDragInfo(EventSource *src) : src(src)
{

}

EventSource * EventOnDragInfo::GetSource() const
{
    return src;
}
