#pragma once
#pragma comment (lib, "Gdiplus.lib")
#include <Windows.h>
#include <gdiplus.h>
#include <thread>
#include <map>
#include <string>
#include <functional>
#include "EntryStateSubject.h"
#include <condition_variable>
#include "EntryStateSubscriber.h"

using namespace Gdiplus;
using namespace std;

/**
 * Also make sure that no nullptrs are being passed
 */
class ApplicationController : public EntryStateSubject
{
public:
	struct WinEntryArgs
	{
		HINSTANCE hInstance;
		HINSTANCE hPrevInstance;
		LPSTR lpCmdLine;
		int nCmdShow;
	};

    const WinEntryArgs & GetWinEntryArgs();
    const GdiplusStartupOutput & GetGdiOutput();
	void JoinThreads();
    template<typename Function, class ... Args>
	thread& CreateThread(Function&& f, const string&& tag, Args&& ... args)
    {
        auto thread = std::make_unique<std::thread>(f, args ...);
        auto& threadRef = *thread;
        threads.emplace(std::make_pair(tag, std::move(thread)));
        return threadRef;
    }
    static void Create(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    static ApplicationController* GetApplicationController();
	~ApplicationController();
    void NotifyOnEntryStart() override;
    void NotifyOnEntryEnd() override;
    void AddEntryStateSubscriber(EntryStateSubscriber *subscriber) override;
    void RemoveEntryStateSubscriber(EntryStateSubscriber *subscriber) override;
    void WaitForEntryToFinish() override;

    static LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    ApplicationController(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    std::vector<EntryStateSubscriber*> subscribers;
    std::multimap<std::string, std::unique_ptr<std::thread>> threads;
    WinEntryArgs args;

    static ApplicationController* applicationController;
    ULONG token = 0;
    GdiplusStartupOutput output;
    std::condition_variable entryFinished;
    std::mutex entryFinishedMutex;
    bool entryFinishedSignaled = false;
};

