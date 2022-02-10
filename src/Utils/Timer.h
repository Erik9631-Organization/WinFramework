#ifndef _LII_TIMERSUBJECT_H
#define _LII_TIMERSUBJECT_H
#include <vector>
#include <mutex>
#include <thread>
#include "TimerSubject.h"

class TimerSubscriber;


class Timer : public TimerSubject
{
public:
    Timer(long long interval);
    Timer();

    void Start();
    void Stop();
    void Wait();
    void SetInterval(long long interval);
    void SetPeriodic(bool periodic);
    long long GetInterval();
    bool IsPeriodic();
    bool IsStopped();

    void AddTimerSubscriber(TimerSubscriber &subscriber) override;
    void RemoveTimerSubscriber(TimerSubscriber &subscriber) override;
    void NotifyOnTimerElapsed(EventOnTimerElapsed e) override;
    ~Timer();
    std::condition_variable* GetTimerEndSignal();

private:
    bool periodic = false;
    long long interval = 0;
    std::vector<std::reference_wrapper<TimerSubscriber>> subscribers;
    void timerCheck();
    std::thread* timerThread = nullptr;
    bool start = false;
    bool signaled = true;
    std::condition_variable* timerEndSingal;
};

#endif
