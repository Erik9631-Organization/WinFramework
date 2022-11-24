#pragma once
#include <thread>
#include <map>
#include <string>
#include <functional>
#include <condition_variable>

/**
 * Also make sure that no nullptrs are being passed
 */
class ApplicationController
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
    static ApplicationController* GetApplicationController();
private:
    std::multimap<std::string, std::unique_ptr<std::thread>> threads;

    static ApplicationController* applicationController;
    bool entryFinishedSignaled = false;
};

