//
// Created by Erik on 08/10/22.
//

#include "EventCursorLockInfo.h"

EventCursorLockInfo::EventCursorLockInfo(bool cursorLockInfo, EventSource *src)
{
    this->cursorLockInfo = cursorLockInfo;
    this->src = src;
}

const bool &EventCursorLockInfo::GetCursorLockInfo() const
{
    return cursorLockInfo;
}

EventSource * EventCursorLockInfo::GetSource() const
{
    return src;
}
