//
// Created by Erik on 08/10/22.
//

#include "EventCursorLockInfo.h"

EventCursorLockInfo::EventCursorLockInfo(bool cursorLockInfo, const std::any &src)
{
    this->cursorLockInfo = cursorLockInfo;
    this->src = std::move(src);
}

const bool &EventCursorLockInfo::GetCursorLockInfo()
{
    return cursorLockInfo;
}

const std::any &EventCursorLockInfo::GetSrc()
{
    return src;
}
