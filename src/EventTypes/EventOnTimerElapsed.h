//
// Created by Erik on 1/19/2022.
//

#ifndef LII_EVENTONTIMERELAPSED_H
#define LII_EVENTONTIMERELAPSED_H


class EventOnTimerElapsed
{
public:
    EventOnTimerElapsed(long long elapsedTime);
    long long GetElapsedTime();
private:
    long long elapsedTime;
};


#endif //LII_EVENTONTIMERELAPSED_H
