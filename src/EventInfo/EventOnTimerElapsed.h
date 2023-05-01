//
// Created by Erik on 1/19/2022.
//

#ifndef LII_EVENTONTIMERELAPSED_H
#define LII_EVENTONTIMERELAPSED_H


class EventOnTimerElapsed
{
public:
    explicit EventOnTimerElapsed(long long elapsedTime);
    long long GetElapsedTime() const;
private:
    long long elapsedTime;
};


#endif //LII_EVENTONTIMERELAPSED_H
