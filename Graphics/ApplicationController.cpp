#include "ApplicationController.h"
#include "CoreWindowFrame.h"
ApplicationController::WinEntryArgs ApplicationController::args;
vector<CoreWindowFrame*>* ApplicationController::windows = new vector<CoreWindowFrame*>();
ULONG ApplicationController::token = 0;
GdiplusStartupOutput ApplicationController::output;

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
	GdiplusStartup(&token, &input, &output);
}

ApplicationController::WinEntryArgs ApplicationController::GetWinEntryArgs()
{
	return args;
}

void ApplicationController::SubscribeToMessageLoop(CoreWindowFrame* frame)
{
	windows->push_back(frame);
}

GdiplusStartupOutput ApplicationController::getGdiOutput()
{
	return output;
}

LRESULT ApplicationController::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	for (CoreWindowFrame* i : *windows)
	{
		if (i->GetWindowHandle() == hwnd)
			i->ProcessMessage(uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

ApplicationController::~ApplicationController()
{
	GdiplusShutdown(token);
}
