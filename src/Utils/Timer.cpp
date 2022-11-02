#include "Timer.h"
#include <chrono>
#include <iostream>
#include "TimerSubscriber.h"
#include "Core/Windows/WindowsCore.h"
#include <Windows.h>
#include <processthreadsapi.h>
using namespace std::chrono;


void Timer::timerCheck()
{
	long long lastTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	while (start)
	{
	    signaled = false;
	    long long currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	    long long elapsedTime = currentTime - lastTime;
	    //CoreWindow::ConsoleWrite(to_string(elapsedTime) + ">=" + to_string(interval));
		if (elapsedTime >= interval)
		{
			lastTime = currentTime;
			auto e = EventOnTimerElapsed(interval);
            NotifyOnTimerElapsed(e);
            signaled = true;
			if (!IsPeriodic())
				break;
			else
				timerEndSingal->notify_all();
		}
		std::this_thread::sleep_for(2ms);
	}

	start = false;
	signaled = true;
	timerThread = nullptr;
	timerEndSingal->notify_all();
}

void Timer::Start()
{
	if (!start)
	{
		start = true;
		signaled = false;
		timerThread = new std::thread(&Timer::timerCheck, this);
		SetThreadPriority(timerThread->native_handle(), REALTIME_PRIORITY_CLASS);
	}

}

void Timer::Stop()
{
    if(timerThread == nullptr)
        return;
    start = false;
    signaled = true;
	timerThread->join();
	timerThread = nullptr;
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
