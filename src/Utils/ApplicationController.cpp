#include "ApplicationController.h"
#include "Components/CoreWindow.h"
#include <thread>
#include <functional>
#if defined(_M_X64)
#define USER_DATA (GWLP_USERDATA)
#else
#define USER_DATA (GWL_USERDATA)
#endif


ApplicationController* ApplicationController::applicationController = nullptr;

ApplicationController::ApplicationController(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	this->args.hInstance = hInstance;
	this->args.hPrevInstance = hPrevInstance;
	this->args.lpCmdLine = lpCmdLine;
	this->args.nCmdShow = nCmdShow;

	//GDIPlus
	GdiplusStartupInput input;
	input.GdiplusVersion = 1; 
	input.SuppressBackgroundThread = FALSE;
	input.DebugEventCallback = NULL;
	GdiplusStartup(reinterpret_cast<ULONG_PTR *>(&token), &input, &output);
}

const ApplicationController::WinEntryArgs & ApplicationController::GetWinEntryArgs()
{
	return args;
}

const GdiplusStartupOutput & ApplicationController::GetGdiOutput()
{
	return output;
}

void ApplicationController::JoinThreads()
{
	for (auto& i : threads)
	{
        if(i.second->joinable())
            i.second->join();
	}
}

LRESULT ApplicationController::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    CoreWindow* frame = reinterpret_cast<CoreWindow*>(GetWindowLongPtr(hwnd, USER_DATA));
	if (frame != nullptr)
		frame->ProcessMessage(uMsg, wParam, lParam);

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

ApplicationController::~ApplicationController()
{
	GdiplusShutdown(token);
}

void ApplicationController::Create(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if(ApplicationController::applicationController != nullptr)
        return;
    ApplicationController::applicationController = new ApplicationController(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
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
