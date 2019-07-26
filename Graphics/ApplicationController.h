#pragma once
#pragma comment (lib, "Gdiplus.lib")
#include <Windows.h>
#include <vector>
#include <gdiplus.h>
using namespace Gdiplus;
using namespace std;
class CoreWindowFrame;
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
	static vector<reference_wrapper<CoreWindowFrame>> windows;
	static LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static WinEntryArgs GetWinEntryArgs();
	static void SubscribeToMessageLoop(CoreWindowFrame& frame);
	static GdiplusStartupOutput getGdiOutput();
	~ApplicationController();
private:
	static WinEntryArgs args;
	static ULONG token;
	static GdiplusStartupOutput output;
};

