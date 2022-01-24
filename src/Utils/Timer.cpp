#include "Timer.h"
#include <chrono>
#include <iostream>
#include "TimerSubscriber.h"
using namespace std::chrono;

void Timer::timerCheck()
{
	int lastTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	while (start)
	{
		int currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		int elapsedTime = currentTime - lastTime;
		if (elapsedTime >= interval)
		{
			lastTime = currentTime;
			EventOnTimerElapsed e = EventOnTimerElapsed(interval);
            NotifyOnTimerElapsed(e);
			if (!IsPeriodic())
				break;
		}
		std::this_thread::sleep_for(5ms);
	}

	start = false;
	signaled = true;
	timerThread = nullptr;
	timerEndSingal->notify_all();
}

void Timer::Start()
{
	if (timerThread == nullptr)
	{
		start = true;
		signaled = false;
		timerThread = new std::thread(&Timer::timerCheck, this);
	}

}

void Timer::Stop()
{
    if(IsStopped())
        return;
    start = false;
	std::mutex timerMutex;
	std::unique_lock<std::mutex>lock(timerMutex);
	timerEndSingal->wait(lock, [=] {return signaled; });
}

void Timer::SetInterval(long long interval)
{
	this->interval = interval;
}

void Timer::SetPeriodic(bool periodic)
{
	this->periodic = periodic;
}

long long Timer::GetInterval()
{
	return interval;
}

bool Timer::IsPeriodic()
{
	return periodic;
}

Timer::Timer() : Timer(0)
{

}

Timer::Timer(long long interval)
{
	timerEndSingal = new std::condition_variable();
	this->interval = interval;
}


Timer::~Timer()
{
	Stop();
	delete timerEndSingal;
	delete timerThread;
}

void Timer::AddTimerSubscriber(TimerSubscriber &subscriber)
{
    subscribers.emplace_back(subscriber);
}

void Timer::RemoveTimerSubscriber(TimerSubscriber &removeRef)
{
    for(auto i = subscribers.begin(); i != subscribers.end(); i++)
    {
        if(&(i->get()) == &removeRef)
        {
            subscribers.erase(i);
            break;
        }
    }
}

void Timer::NotifyOnTimerElapsed(EventOnTimerElapsed e)
{
    for (TimerSubscriber& subscriber : subscribers)
        subscriber.OnTimerElapsed(e);
}

std::condition_variable *Timer::GetTimerEndSignal()
{
    return timerEndSingal;
}

bool Timer::IsStopped()
{
    return !start;
}

void Timer::Wait()
{
    if(IsStopped())
        return;
    std::mutex timerMutex;
    std::unique_lock<std::mutex>lock(timerMutex);
    timerEndSingal->wait(lock, [=] {return signaled; });
}
