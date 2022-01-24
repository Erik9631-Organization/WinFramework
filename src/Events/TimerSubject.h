//
// Created by Erik on 1/19/2022.
//

#ifndef LII_TIMERSUBJECT_H
#define LII_TIMERSUBJECT_H
class TimerSubscriber;
#include "EventOnTimerElapsed.h"

class TimerSubject
{
public:
    virtual void AddTimerSubscriber(TimerSubscriber& subscriber) = 0;
    virtual void RemoveTimerSubscriber(TimerSubscriber& subscriber) = 0;
    virtual void NotifyOnTimerElapsed(EventOnTimerElapsed e) = 0;
};


#endif //LII_TIMERSUBJECT_H
