#pragma once
#pragma comment (lib, "Gdiplus.lib")
#include <Windows.h>
#include <vector>
#include <gdiplus.h>
#include <thread>
using namespace Gdiplus;
using namespace std;
class CoreWindow;
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
private:
	static vector<thread*> threads;
	static WinEntryArgs args;
	static ULONG token;
	static GdiplusStartupOutput output;
};

