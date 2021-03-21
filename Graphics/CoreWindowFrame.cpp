#include "CoreWindowFrame.h"
#include <Windows.h>
#include <iostream>
#include <functional>
#include "Resizable.h"
#include "EventResizeInfo.h"
#include "RenderEventInfo.h"
#include <stack>
#include "EventMouseStateInfo.h"
#include "EventKeyStateInfo.h"

HDC windowHdc;
using namespace std;

void CoreWindowFrame::MessageLoop()
{
	MSG currentMsg;
	while (GetMessage(&currentMsg, NULL, NULL, NULL))
	{
		TranslateMessage(&currentMsg);
		DispatchMessage(&currentMsg);
	}
}

HDC CoreWindowFrame::CreateGraphicsBuffer()
{
	windowHdc = GetDC(windowHandle);
	secondaryBuffer = CreateCompatibleDC(windowHdc);
	currentBitmap = CreateCompatibleBitmap(windowHdc, wrapperFrame.GetWidth(), wrapperFrame.GetHeight());
	SelectObject(secondaryBuffer, currentBitmap);
	return secondaryBuffer;
}

void CoreWindowFrame::CleanGraphicsBuffer()
{
	ReleaseDC(windowHandle, secondaryBuffer);
	ReleaseDC(windowHandle, windowHdc);
	DeleteDC(secondaryBuffer);
	DeleteDC(windowHdc);
	DeleteObject(currentBitmap);
}

void CoreWindowFrame::RenderGraphics(HDC graphicsBuffer) // BackBuffer
{
	BitBlt(windowHdc, 0, 0, wrapperFrame.GetWidth(), wrapperFrame.GetHeight(), secondaryBuffer, 0, 0, MERGECOPY);
}
/**
* Components should be gettable from the WindowFrame
* Should iterate through components as a tree. First you set the clipping region with the parents graphics and his graphics, then you pass render event and let it draw
*/



void CoreWindowFrame::AssignGraphicsToComponents()
{
	Rect rootViewport = Rect(0, 0, wrapperFrame.GetWidth() + 1, wrapperFrame.GetHeight() + 1);
	assignGraphicsToNodes(wrapperFrame.GetComponentNode(), rootViewport);
}

void CoreWindowFrame::assignGraphicsToNodes(MultiTree<Component&>& node, Rect parentViewport)
{
	Graphics graphics(secondaryBuffer);
	graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

	Gdiplus::Rect viewport;
	if(!node.IsRoot())
	{
		viewport = Rect(node.GetValue().GetViewportAbsolutePosition(), node.GetValue().GetViewportAbsoluteSize());
		graphics.SetClip(viewport);
		graphics.IntersectClip(parentViewport);
	}
	else
		viewport = parentViewport;

	RenderEventInfo renderEvent = RenderEventInfo(&graphics);
	node.GetValue().OnRender(renderEvent);

	for (int i = 0; i < node.GetNodeCount(); i++)
		assignGraphicsToNodes(node.Get(i), viewport);
	return;
}

void CoreWindowFrame::NotifyMouseState(Gdiplus::Point point)
{
	/*for (int i = 0; i < wrapperFrame.GetComponentNode().GetNodeCount(); i++)
	{
		if (wrapperFrame.GetComponentNode().Get(i).GetValue().ColidesWithPoint(point));
			wrapperFrame.NotifyOnMouseMove(EventMouseStateInfo(point, 0));
	}*/

}

void CoreWindowFrame::ProcessKeyState(UINT msg, WPARAM wParam, LPARAM lParam)
{
	HKL currentLayout = GetKeyboardLayout(0); // For the current thread

	wchar_t unicodeKey = 0;
	unsigned int scanCode = MapVirtualKeyA(wParam, MAPVK_VK_TO_VSC);
	BYTE keyboardState[256];
	bool state = GetKeyboardState(keyboardState);
	int returnValue = ToUnicodeEx(wParam, scanCode, keyboardState, &unicodeKey, 1, 0, currentLayout);
	if (msg == WM_KEYDOWN)
	{
		if( !(lParam & 1073741824) ) //30th bit (Bit count from 0)	The previous key state. The value is 1 if the key is down before the message is sent, or it is zero if the key is up.
			wrapperFrame.NotifyOnKeyDown(EventKeyStateInfo(nullptr, wParam, unicodeKey, keyboardState));
		else
			wrapperFrame.NotifyOnKeyPressed(EventKeyStateInfo(nullptr, wParam, unicodeKey, keyboardState));
	}

	else if(msg == WM_KEYUP)
		wrapperFrame.NotifyOnKeyUp(EventKeyStateInfo(nullptr, wParam, unicodeKey, keyboardState));
}

void CoreWindowFrame::ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintInfo;
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOVE:
		wrapperFrame.SetPosition(Gdiplus::Point(*((unsigned short*)&lParam), ((unsigned short*)&lParam)[1]));
		break;
	case WM_SIZE:
		wrapperFrame.SetSize(Gdiplus::Size(*((unsigned short*)&lParam), ((unsigned short*)&lParam)[1]));
		break;
	case WM_PAINT: // Put into function, DrawWindow since it handles WindowDrawing explicitely, from any call not just WM_PAINT
		OnRender(RenderEventInfo(nullptr));
		break;
	case WM_MOUSEMOVE:
		lastMouseX = ((unsigned short*)&lParam)[0];
		lastMouseY = ((unsigned short*)&lParam)[1];
		wrapperFrame.NotifyOnMouseMove(EventMouseStateInfo(Gdiplus::Point(lastMouseX, lastMouseY), 0, &wrapperFrame));
		break;
	case WM_LBUTTONDOWN:
		wrapperFrame.NotifyOnMouseDown(EventMouseStateInfo(Gdiplus::Point(lastMouseX, lastMouseY), wParam, &wrapperFrame));
		break;
	case WM_LBUTTONUP:
		wrapperFrame.NotifyOnMouseUp(EventMouseStateInfo(Gdiplus::Point(lastMouseX, lastMouseY), wParam, &wrapperFrame));
		break;
	case WM_LBUTTONDBLCLK:
		wrapperFrame.NotifyOnMousePressed(EventMouseStateInfo(Gdiplus::Point(lastMouseX, lastMouseY), wParam, &wrapperFrame));
		break;
	case WM_KEYDOWN:
		ProcessKeyState(msg, wParam, lParam);
		break;
	case WM_KEYUP:
		ProcessKeyState(msg, wParam, lParam);
		break;

	}
}

void CoreWindowFrame::RedrawWindow()
{
	InvalidateRgn(GetWindowHandle(), NULL, true);
	UpdateWindow(windowHandle);
}

WindowFrame& CoreWindowFrame::GetWrapperFrame()
{
	return wrapperFrame;
}

HDC * CoreWindowFrame::GetHdc()
{
	return &secondaryBuffer;
}

void CoreWindowFrame::CreateConsole()
{
	AllocConsole();
}

void CoreWindowFrame::ConsoleWrite(string output)
{
	DWORD succWritten;
	output.append("\n");
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output.c_str(), output.size(), &succWritten, NULL);
}

void CoreWindowFrame::UnicodeConsoleWrite(std::wstring output)
{
	DWORD succWritten;
	output.append(L"\n");
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), output.c_str(), output.size(), &succWritten, NULL);
}

CoreWindowFrame::CoreWindowFrame(ApplicationController::WinEntryArgs &args, WindowFrame& wrapperFrame, string windowName) : wrapperFrame(wrapperFrame), renderBehavior(*this)
{
	//Arguments
	HINSTANCE hInstance = args.hInstance;
	HINSTANCE hPrevInstance = args.hPrevInstance;
	LPSTR lpCmdLine = args.lpCmdLine;
	int nCmdShow = args.nCmdShow;

	CreateConsole();
	WNDCLASS* windowInfo = new WNDCLASS;
	memset(windowInfo, 0, sizeof(WNDCLASS));
	windowInfo->style = CS_HREDRAW | CS_VREDRAW;
	windowInfo->lpfnWndProc = (WNDPROC)ApplicationController::WindowProc;
	windowInfo->cbClsExtra = NULL;
	windowInfo->cbWndExtra = NULL;
	windowInfo->hInstance = hInstance;
	windowInfo->hIcon = NULL;
	windowInfo->hCursor = LoadCursor(NULL, IDC_ARROW);
	windowInfo->hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowInfo->lpszMenuName = NULL;
	windowInfo->lpszClassName = windowName.c_str();

	if (!RegisterClass(windowInfo))
	{
		ConsoleWrite("Register Class error: " + to_string(GetLastError()));
		system("PAUSE");
		exit(0);
	}

	windowHandle = CreateWindow(windowInfo->lpszClassName, windowInfo->lpszClassName, WS_OVERLAPPEDWINDOW, wrapperFrame.GetX(), wrapperFrame.GetY(), wrapperFrame.GetWidth(), wrapperFrame.GetHeight(), NULL, NULL, hInstance, NULL);
	if (!windowHandle)
	{
		ConsoleWrite("Error creating window handle");
		system("PAUSE");
		exit(0);
	}
	SetWindowLong(windowHandle, GWL_USERDATA, (LONG)this);

	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);
	//Critical Section
}


HWND CoreWindowFrame::GetWindowHandle()
{
	return windowHandle;
}

CoreWindowFrame::~CoreWindowFrame()
{
	CleanGraphicsBuffer();
}

void CoreWindowFrame::Repaint()
{
	RedrawWindow();
}

void CoreWindowFrame::AddRenderable(Renderable& renderable)
{
	renderBehavior.AddRenderable(renderable);
}

void CoreWindowFrame::RemoveRenderable(Renderable& renderable)
{
	renderBehavior.RemoveRenderable(renderable);
}

std::vector<std::reference_wrapper<Renderable>> CoreWindowFrame::GetRenderables()
{
	return renderBehavior.GetRenderables();
}


void CoreWindowFrame::OnRender(RenderEventInfo e)
{
	HDC graphicsBuffer = CreateGraphicsBuffer();
	AssignGraphicsToComponents();
	RenderGraphics(graphicsBuffer); //Performs block transfer of the secondary buffer to the primary buffer
	CleanGraphicsBuffer();
	ValidateRgn(GetWindowHandle(), NULL);
	renderBehavior.OnRender(e);
}
