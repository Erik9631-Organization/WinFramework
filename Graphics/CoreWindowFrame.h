#pragma once
#include "WindowFrame.h"
#include <Windows.h>
#include <string>
#include <gdiplus.h>
#include "OnAddListener.h"
#include "ApplicationController.h"

using namespace std;
using namespace Gdiplus;
class CoreWindowFrame
{
private:
	HWND windowHandle;
	int width, height;
	int posX, posY;
	void CreateConsole();
	HDC secondaryBuffer;
	WindowFrame& wrapperFrame;
	HDC CreateGraphicsBuffer();
	void CleanGraphicsBuffer();
	void RenderGraphics(HDC GraphicsBuffer);
	void AssignGraphicsToComponents();
	vector<reference_wrapper<Component>> components;

public:
	CoreWindowFrame(ApplicationController::WinEntryArgs &args, WindowFrame& wrapperFrame,string windowName);
	void ComponentAdded(Component& component);
	void SetPosition(int x, int y);
	void SetSize(int width, int height);
	void MessageLoop();
	void ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	void RedrawWindow();
	WindowFrame& GetWrapperFrame();
	HDC* GetHdc();
	int GetX();
	int GetY();
	HWND GetWindowHandle();
	static void ConsoleWrite(string output);
	~CoreWindowFrame();
};

