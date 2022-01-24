//
// Created by Erik on 1/19/2022.
//

#ifndef LII_TIMERSUBSCRIBER_H
#define LII_TIMERSUBSCRIBER_H
#include "EventOnTimerElapsed.h"


class TimerSubscriber
{
public:
    virtual void OnTimerElapsed(EventOnTimerElapsed e) = 0;
};


#endif //LII_TIMERSUBSCRIBER_H
