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
#include "RenderingProvider.h"

#if defined(_M_X64)
#define USER_DATA (GWLP_USERDATA)
#else
#define USER_DATA (GWL_USERDATA)
#endif

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

LONG CoreWindowFrame::SetWindowAttributes(int index, LONG parameter)
{
	LONG currentAttributes = GetWindowLong(windowHandle, index);
	LONG newAttributes = currentAttributes | parameter;
	LONG returnVal = SetWindowLong(windowHandle, index, newAttributes);
	SetWindowPos(windowHandle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	return returnVal;
}

LONG CoreWindowFrame::RemoveWindowAttributes(int index, LONG parameter)
{
	LONG currentAttributes = GetWindowLong(windowHandle, index);
	LONG newAttributes = currentAttributes & (~parameter);
	LONG returnVal = SetWindowLong(windowHandle, index, newAttributes);
	SetWindowPos(windowHandle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	return returnVal;
}

void CoreWindowFrame::ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintInfo;
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(windowHandle);
		if(!UnregisterClassA(wrapperFrame.GetComponentName().c_str(), hInstance))
			ConsoleWrite("UnRegister Class error: " + to_string(GetLastError()));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOVE:
		wrapperFrame.::UiElement::SetPosition({(float)*((unsigned short*)&lParam), (float)((unsigned short*)&lParam)[1]});
		break;
	case WM_SIZE:
	{
	    unsigned short width = ((unsigned short*)&lParam)[0];
	    unsigned short height = ((unsigned short*)&lParam)[1];
	    preProcessSubject.NotifyOnResizeSubscribers(EventResizeInfo({(float)width, (float)height}, nullptr));
	    wrapperFrame.::UiElement::SetSize({(float)width, (float)height});
	    break;
	}
	case WM_MOUSEMOVE:
	    prevMousePos = mousePos;
        mousePos.SetX(((unsigned short*)&lParam)[0]);
        mousePos.SetY(((unsigned short*)&lParam)[1]);

        mouseDelta = mousePos - prevMousePos;
        //relativePos = mousePos - wrapperFrame.GetPosition();
        wrapperFrame.NotifyOnMouseHover(EventMouseStateInfo(mousePos, mousePos, mouseDelta, 0, &wrapperFrame));
		break;
	case WM_LBUTTONDOWN:
	    wrapperFrame.NotifyOnMouseDown(EventMouseStateInfo(mousePos, relativePos, mouseDelta, wParam, &wrapperFrame));
		break;
	case WM_LBUTTONUP:
	    wrapperFrame.NotifyOnMouseUp(EventMouseStateInfo(mousePos, relativePos, mouseDelta, wParam, &wrapperFrame));
		break;
	case WM_LBUTTONDBLCLK:
	    wrapperFrame.NotifyOnMousePressed(EventMouseStateInfo(mousePos, relativePos, mouseDelta, wParam, &wrapperFrame));
		break;
	case WM_KEYDOWN:
		ProcessKeyState(msg, wParam, lParam);
		break;
	case WM_KEYUP:
		ProcessKeyState(msg, wParam, lParam);
		break;
    case WM_PRINT:
        DefWindowProcA(windowHandle, msg, wParam, lParam); // Call default implementation for WM_PRINT
        break;

	}
}

void CoreWindowFrame::RedrawWindow()
{
    OnRender(nullptr);
	UpdateWindow(windowHandle);
}

void CoreWindowFrame::CloseWindow()
{
	PostMessage(windowHandle, WM_CLOSE, NULL, NULL);
}

WindowFrame& CoreWindowFrame::GetWrapperFrame()
{
	return wrapperFrame;
}

HDC * CoreWindowFrame::GetHdc()
{
	return &secondaryDc;
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

void CoreWindowFrame::UpdateScale()
{
	SetWindowPos(windowHandle, NULL, wrapperFrame.GetX(), wrapperFrame.GetY(), wrapperFrame.GetWidth(), wrapperFrame.GetHeight(), SWP_SHOWWINDOW | SWP_DRAWFRAME);
}

CoreWindowFrame::CoreWindowFrame(ApplicationController::WinEntryArgs &args, WindowFrame& wrapperFrame, string windowName, LONG style) : wrapperFrame(wrapperFrame), renderBehavior(*this)
{
	//Arguments
	hInstance = args.hInstance;
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
	windowHandle = CreateWindow(windowInfo->lpszClassName, windowInfo->lpszClassName, style, wrapperFrame.GetX(), wrapperFrame.GetY(), wrapperFrame.GetWidth(), wrapperFrame.GetHeight(), NULL, NULL, hInstance, NULL);

	if (!windowHandle)
	{
		ConsoleWrite("Error creating window handle");
		system("PAUSE");
		exit(0);
	}
	SetWindowLongPtr(windowHandle, USER_DATA, (LONG_PTR)this);

	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);
	secondaryBitmap = CreateCompatibleBitmap(GetWindowDC(windowHandle), wrapperFrame.GetWidth(), wrapperFrame.GetHeight());

	//Critical Section end
}


HWND CoreWindowFrame::GetWindowHandle()
{
	return windowHandle;
}

CoreWindowFrame::~CoreWindowFrame()
{

}

void CoreWindowFrame::Repaint()
{
	RedrawWindow();
}

void CoreWindowFrame::AddRenderable(Renderable &renderable)
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
    if(renderingProvider != nullptr)
        renderingProvider->AssignRenderer();
}

void CoreWindowFrame::AddOnResizePreProcessSubsriber(ResizeSubscriber &subscriber)
{
    preProcessSubject.AddOnResizeSubscriber(subscriber);
}

RenderingProvider *CoreWindowFrame::GetRenderingProvider()
{
    return renderingProvider;
}

void CoreWindowFrame::SetRenderingProvider(RenderingProvider& provider)
{
    this->renderingProvider = &provider;
}

void CoreWindowFrame::MsgSubject::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    for(ResizeSubscriber& subscriber : resizeSubscribers)
        subscriber.OnResize(event);

}

void CoreWindowFrame::MsgSubject::AddOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizeSubscribers.emplace_back(subscriber);
}

void CoreWindowFrame::MsgSubject::RemoveOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    for(auto iterator = resizeSubscribers.begin(); iterator != resizeSubscribers.end(); iterator++)
    {
        if(&iterator->get() == &subscriber)
        {
            resizeSubscribers.erase(iterator);
            return;
        }
    }
}
