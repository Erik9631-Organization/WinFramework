#pragma once
#pragma comment (lib, "Gdiplus.lib")
#include <Windows.h>
#include <vector>
#include <gdiplus.h>
#include <thread>
#include "DestroySubjectBehavior.h"
#include "StartSubjectBehavior.h"

using namespace Gdiplus;
using namespace std;
class CoreWindow;

/**
 * TODO Finish DestroySubject event types
 * TODO Finish StartSubject event types
 * Also make sure that no nullptrs are being passed
 */
class ApplicationController
{
public:
	struct WinEntryArgs
	{
		HINSTANCE hInstance;
		HINSTANCE hPrevInstance;
		LPSTR lpCmdLine;
		int nCmdShow;
	};
	ApplicationController(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	static vector<reference_wrapper<CoreWindow>> windows;
	static LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static WinEntryArgs GetWinEntryArgs();
	static void SubscribeToWinProc(CoreWindow& frame);
	static GdiplusStartupOutput getGdiOutput();
	static void JoinThreads();
	static void AddThread(thread* joinableThread);
	~ApplicationController();
    static void NotifyOnStart();
    static void NotifyOnDestroy();
    static void AddOnStartSubscriber(StartSubscriber* subscriber);
    static void AddOnDestroySubscriber(DestroySubscriber* subscriber);
private:
	static vector<thread*> threads;
	static WinEntryArgs args;
	static ULONG token;
	static GdiplusStartupOutput output;
    static DestroySubjectBehavior* destroySubjectBehavior;
    static StartSubjectBehavior* startSubjectBehavior;
};

