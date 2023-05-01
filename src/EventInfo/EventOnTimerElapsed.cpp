//
// Created by Erik on 1/19/2022.
//

#include "EventOnTimerElapsed.h"

EventOnTimerElapsed::EventOnTimerElapsed(long long int elapsedTime)
{
    this->elapsedTime = elapsedTime;
}

long long EventOnTimerElapsed::GetElapsedTime() const
{
    return elapsedTime;
}
