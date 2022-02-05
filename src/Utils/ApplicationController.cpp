#include "ApplicationController.h"
#include "Components/CoreWindow.h"
#include <thread>
#if defined(_M_X64)
#define USER_DATA (GWLP_USERDATA)
#else
#define USER_DATA (GWL_USERDATA)
#endif



ApplicationController::WinEntryArgs ApplicationController::args;
vector<reference_wrapper<CoreWindow>> ApplicationController::windows = vector<reference_wrapper<CoreWindow>>();
ULONG ApplicationController::token = 0;
GdiplusStartupOutput ApplicationController::output;
vector<thread*> ApplicationController::threads;

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

ApplicationController::WinEntryArgs ApplicationController::GetWinEntryArgs()
{
	return args;
}

void ApplicationController::SubscribeToWinProc(CoreWindow& frame)
{
	windows.push_back(frame);
}

GdiplusStartupOutput ApplicationController::getGdiOutput()
{
	return output;
}

void ApplicationController::JoinThreads()
{
	for (thread* i : threads)
	{
		if(i->joinable())
			i->join();
	}
}

void ApplicationController::AddThread(thread* joinableThread)
{
	threads.push_back(joinableThread);
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
