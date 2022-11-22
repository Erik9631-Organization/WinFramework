#include "ApplicationController.h"
#include <thread>
#if defined(_M_X64)
#define USER_DATA (GWLP_USERDATA)
#else
#define USER_DATA (GWL_USERDATA)
#endif


ApplicationController* ApplicationController::applicationController = nullptr;

ApplicationController::ApplicationController()
{

}

void ApplicationController::JoinThreads()
{
	for (auto& i : threads)
	{
        if(i.second->joinable())
            i.second->join();
	}
}

ApplicationController::~ApplicationController()
{

}

void ApplicationController::Create()
{
    if(ApplicationController::applicationController != nullptr)
        return;
    ApplicationController::applicationController = new ApplicationController();
}

void ApplicationController::NotifyOnEntryStart()
{
    for(EntryStateSubscriber* subscriber : subscribers)
        subscriber->OnEntryStart();
}

void ApplicationController::NotifyOnEntryEnd()
{
    for(EntryStateSubscriber* subscriber : subscribers)
        subscriber->OnEntryEnd();
    std::unique_lock<std::mutex> entryFinishedLock{(entryFinishedMutex)};
    entryFinishedSignaled = true;
    entryFinished.notify_all();
}

ApplicationController *ApplicationController::GetApplicationController()
{
    return applicationController;
}

void ApplicationController::AddEntryStateSubscriber(EntryStateSubscriber *subscriber)
{
    subscribers.push_back(subscriber);
}

void ApplicationController::RemoveEntryStateSubscriber(EntryStateSubscriber *subscriber)
{
    for(auto it = subscribers.begin(); it != subscribers.end(); it++)
    {
        if(*it == subscriber)
        {
            subscribers.erase(it);
            return;
        }
    }
}

void ApplicationController::WaitForEntryToFinish()
{
    std::unique_lock<std::mutex> entryFinishedLock{(entryFinishedMutex)};
    entryFinished.wait(entryFinishedLock, [=]{return entryFinishedSignaled;});
}
