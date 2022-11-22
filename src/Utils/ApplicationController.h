#pragma once
#include <thread>
#include <map>
#include <string>
#include <functional>
#include "EntryStateSubject.h"
#include <condition_variable>
#include "EntryStateSubscriber.h"

/**
 * Also make sure that no nullptrs are being passed
 */
class ApplicationController : public EntryStateSubject
{
public:
	void JoinThreads();
    template<typename Function, class ... Args>
	std::thread& CreateThread(Function&& f, const std::string&& tag, Args&& ... args)
    {
        auto thread = std::make_unique<std::thread>(f, args ...);
        auto& threadRef = *thread;
        threads.emplace(std::make_pair(tag, std::move(thread)));
        return threadRef;
    }
    static void Create();
    static ApplicationController* GetApplicationController();
	~ApplicationController();
    void NotifyOnEntryStart() override;
    void NotifyOnEntryEnd() override;
    void AddEntryStateSubscriber(EntryStateSubscriber *subscriber) override;
    void RemoveEntryStateSubscriber(EntryStateSubscriber *subscriber) override;
    void WaitForEntryToFinish() override;
private:
    ApplicationController();
    std::vector<EntryStateSubscriber*> subscribers;
    std::multimap<std::string, std::unique_ptr<std::thread>> threads;

    static ApplicationController* applicationController;
    std::condition_variable entryFinished;
    std::mutex entryFinishedMutex;
    bool entryFinishedSignaled = false;
};

