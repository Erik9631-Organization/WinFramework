//
// Created by Erik on 1/19/2022.
//

#include "EventOnTimerElapsed.h"

EventOnTimerElapsed::EventOnTimerElapsed(long long elapsedTime, EventSource *source)
{
    this->elapsedTime = elapsedTime;
}

long long EventOnTimerElapsed::GetElapsedTime() const
{
    return elapsedTime;
}

EventSource * EventOnTimerElapsed::GetSource() const
{
    return source;
}
