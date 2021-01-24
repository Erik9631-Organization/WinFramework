#include "CoreWindowFrame.h"
#include <Windows.h>
#include <iostream>
#include <functional>
#include "Resizable.h"
#include "EventResizeInfo.h"

HDC windowHdc;
using namespace std;

void CoreWindowFrame::MessageLoop()
{
	MSG currentMsg;
	while (GetMessage(&currentMsg, windowHandle, NULL, NULL))
	{
		TranslateMessage(&currentMsg);
		DispatchMessage(&currentMsg);
	}
}

HDC CoreWindowFrame::CreateGraphicsBuffer()
{
	windowHdc = GetDC(windowHandle);
	secondaryBuffer = CreateCompatibleDC(windowHdc);
	HBITMAP map = CreateCompatibleBitmap(windowHdc, size.Width, size.Height);
	SelectObject(secondaryBuffer, map);
	return secondaryBuffer;
}

void CoreWindowFrame::CleanGraphicsBuffer()
{
	ReleaseDC(windowHandle, secondaryBuffer);
	ReleaseDC(windowHandle, windowHdc);
	DeleteDC(secondaryBuffer);
	DeleteDC(windowHdc);
}

void CoreWindowFrame::RenderGraphics(HDC graphicsBuffer) // BackBuffer
{
	BitBlt(windowHdc, 0, 0, size.Width, size.Height, secondaryBuffer, 0, 0, MERGECOPY);
}
/**
* Components should be gettable from the WindowFrame
* Should iterate through components as a tree. First you set the clipping region with the parents graphics and his graphics, then you pass render event and let it draw
*/
void CoreWindowFrame::AssignGraphicsToComponents()
{
	for (Component& i : components) //Each graphics component should have its own bitmap. The bitmap should have the size of the component. The bitmaps should be merged. 
	{
		Graphics graphics(secondaryBuffer); //Rendering is basically a tree
		i.Paint(graphics); //Handle clipping via graphics.setClip and use AND (Intersect)
	}
}

void CoreWindowFrame::ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintInfo;
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		delete this;
		break;
	case WM_MOVE:
		position.X = *((unsigned short*)&lParam);
		position.Y = ((unsigned short*)&lParam)[1];
		NotifyOnMoveSubscribers(EventMoveInfo(position));
		break;
	case WM_SIZE:
		size.Width = *((unsigned short*)&lParam);
		size.Height = ((unsigned short*)&lParam)[1];
		NotifyOnResizeSubscribers(EventResizeInfo(size));
		break;
	case WM_PAINT: // Put into function, DrawWindow since it handles WindowDrawing explicitely, from any call not just WM_PAINT
		HDC graphicsBuffer = CreateGraphicsBuffer();
		AssignGraphicsToComponents();
		RenderGraphics(graphicsBuffer); //Performs block transfer of the secondary buffer to the primary buffer
		CleanGraphicsBuffer();
		ValidateRgn(GetWindowHandle(), NULL);
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

CoreWindowFrame::CoreWindowFrame(ApplicationController::WinEntryArgs &args, WindowFrame& wrapperFrame, string windowName) : wrapperFrame(wrapperFrame)
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

	size.Width = 800;
	size.Height = 600;
	position.X = 800;
	position.Y = 600;

	if (!RegisterClass(windowInfo))
	{
		ConsoleWrite("Register Class error" + to_string(GetLastError()));
		system("PAUSE");
		exit(0);
	}

	windowHandle = CreateWindow(windowInfo->lpszClassName, windowInfo->lpszClassName, WS_OVERLAPPEDWINDOW, size.Width, size.Height, position.X, position.Y, NULL, NULL, hInstance, NULL);
	if (!windowHandle)
	{
		ConsoleWrite("Error creating window handle");
		system("PAUSE");
		exit(0);
	}
	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);
	//components = new vector<reference_wrapper<Component>>();
	//Critical Section
}

void CoreWindowFrame::ComponentAdded(Component & component)
{
	components.push_back(component);
	RedrawWindow();
}


int CoreWindowFrame::GetX()
{
	return position.X;
}

int CoreWindowFrame::GetY()
{
	return position.Y;
}

HWND CoreWindowFrame::GetWindowHandle()
{
	return windowHandle;
}

CoreWindowFrame::~CoreWindowFrame()
{
	CleanGraphicsBuffer();
}

void CoreWindowFrame::NotifyOnResizeSubscribers(EventResizeInfo event)
{
	for (ResizeSubscriber& subscriber : resizeSubscribers)
		subscriber.OnResize(event);
}

void CoreWindowFrame::AddOnResizeSubscriber(ResizeSubscriber& subscriber)
{
	resizeSubscribers.push_back(subscriber);
}

void CoreWindowFrame::RemoveOnResizeSubscriber(ResizeSubscriber& subscriber)
{
	std::vector<reference_wrapper<ResizeSubscriber>>::iterator it = resizeSubscribers.begin();
	for (int i = 0; i < resizeSubscribers.size(); i++, it++)
	{
		if (&resizeSubscribers.at(i).get() == &subscriber)
			resizeSubscribers.erase(it);
	}
}

Gdiplus::Size CoreWindowFrame::GetSize()
{
	return size;
}

int CoreWindowFrame::GetWidth()
{
	return size.Width;
}

int CoreWindowFrame::GetHeight()
{
	return size.Height;
}

void CoreWindowFrame::SetSize(Gdiplus::Size size)
{
	this->size = size;
	SetWindowPos(windowHandle, NULL, NULL, NULL, size.Width, size.Height, SWP_NOMOVE);
}

void CoreWindowFrame::SetWidth(int width)
{
	SetSize(Size(width, size.Height));
}

void CoreWindowFrame::SetHeight(int height)
{
	SetSize(Size(height, size.Width));
}

Gdiplus::Point CoreWindowFrame::GetPosition()
{
	return Point(this->GetX(), this->GetY());
}

void CoreWindowFrame::SetPosition(Gdiplus::Point position)
{
	this->position = position;
	SetWindowPos(windowHandle, NULL, position.X, position.Y, NULL, NULL, SWP_NOSIZE);
}

void CoreWindowFrame::SetX(int x)
{
	SetPosition(Point(x, position.Y));
}

void CoreWindowFrame::SetY(int y)
{
	SetPosition(Point(position.X, y));
}

void CoreWindowFrame::AddOnMoveSubscriber(MoveSubscriber& subscriber)
{
	moveSubscribers.push_back(subscriber);
}

void CoreWindowFrame::RemoveOnMoveSubscriber(MoveSubscriber& subscriber)
{
	std::vector<reference_wrapper<MoveSubscriber>>::iterator it = moveSubscribers.begin();
	for (int i = 0; i < moveSubscribers.size(); i++, it++)
	{
		if (&moveSubscribers.at(i).get() == &subscriber)
			moveSubscribers.erase(it);
	}
}

void CoreWindowFrame::NotifyOnMoveSubscribers(EventMoveInfo event)
{
	for (MoveSubscriber& subscriber : moveSubscribers)
		subscriber.OnMove(event);
}

void CoreWindowFrame::SetPosition(int x, int y)
{
	SetPosition(Point(x, y));
}

void CoreWindowFrame::SetSize(int width, int height)
{
	SetSize(Size(width, height));
}
