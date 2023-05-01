//
// Created by Erik on 1/19/2022.
//

#ifndef LII_EVENTONTIMERELAPSED_H
#define LII_EVENTONTIMERELAPSED_H


#include "Event.h"

class EventOnTimerElapsed : public Event
{
public:
    explicit EventOnTimerElapsed(long long elapsedTime, EventSource *source);
    [[nodiscard]] long long GetElapsedTime() const;

    [[nodiscard]] EventSource * GetSource() const override;

private:
    EventSource* source = nullptr;
    long long elapsedTime;
};


#endif //LII_EVENTONTIMERELAPSED_H
