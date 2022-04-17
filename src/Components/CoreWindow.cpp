#include "CoreWindow.h"
#include <Windows.h>
#include <iostream>
#include <functional>
#include "api/Resizable.h"
#include "EventResizeInfo.h"
#include "RenderEventInfo.h"
#include <stack>
#include "EventMouseStateInfo.h"
#include "EventKeyStateInfo.h"
#include "RenderingProvider.h"
#include <processthreadsapi.h>
#include "Messages.h"
#include <chrono>
#include "GdiRenderer.h"
#include "Vector2Int.h"

#if defined(_M_X64)
#define USER_DATA (GWLP_USERDATA)
#else
#define USER_DATA (GWL_USERDATA)
#endif

HDC windowHdc;
using namespace std;
using namespace chrono;

void CoreWindow::WindowsMessageLoop()
{
	MSG currentMsg;
	while (processMessages)
	{
//	    if(!eventBased)
//	        fpsTimer.Start();

	    if(eventBased)
	        GetMessage(&currentMsg, NULL, NULL, NULL);
	    else
	        if(!PeekMessage(&currentMsg, NULL, NULL, NULL, PM_REMOVE))
	        {
	            //memset(&currentMsg, 0, sizeof(MSG));
	            currentMsg.hwnd = GetWindowHandle();
	            currentMsg.message = LiiMessages::UPDATE;
	        }
		TranslateMessage(&currentMsg);
		DispatchMessage(&currentMsg);
//		if(!eventBased)
//		    fpsTimer.Wait();
		//CoreWindow::ConsoleWrite(to_string(current - start));
	}
}
void CoreWindow::ProcessKeyState(UINT msg, WPARAM wParam, LPARAM lParam)
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

LONG CoreWindow::SetWindowAttributes(int index, LONG parameter)
{
	LONG currentAttributes = GetWindowLong(windowHandle, index);
	LONG newAttributes = currentAttributes | parameter;
	LONG returnVal = SetWindowLong(windowHandle, index, newAttributes);
	SetWindowPos(windowHandle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	return returnVal;
}

LONG CoreWindow::RemoveWindowAttributes(int index, LONG parameter)
{
	LONG currentAttributes = GetWindowLong(windowHandle, index);
	LONG newAttributes = currentAttributes & (~parameter);
	LONG returnVal = SetWindowLong(windowHandle, index, newAttributes);
	SetWindowPos(windowHandle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	return returnVal;
}

void CoreWindow::ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
    updateFinished = false;
    //CoreWindow::ConsoleWrite("Update started");
	PAINTSTRUCT paintInfo;
	//Wait for sync to finish.
	if(renderingProvider != nullptr)
	{
	    //CoreWindow::ConsoleWrite("Waiting for sync to finish...");
	    renderingProvider->WaitForSyncToFinish();
	    //CoreWindow::ConsoleWrite("Sync finished, continuing update");
	}

	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(windowHandle);
		if(!UnregisterClassA(wrapperFrame.GetComponentName().c_str(), hInstance))
			ConsoleWrite("UnRegister Class error: " + to_string(GetLastError()));
		processMessages = false;
		//CoreWindow::ConsoleWrite("Update thread ending!");
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOVE:
		wrapperFrame.::UiElement::SetPosition({(float)*((unsigned short*)&lParam), (float)((unsigned short*)&lParam)[1]});
        UpdateLockCursor();
		break;
	case WM_SIZE:
	{
	    unsigned short width = ((unsigned short*)&lParam)[0];
	    unsigned short height = ((unsigned short*)&lParam)[1];
	    preProcessSubject.NotifyOnResizeSubscribers(EventResizeInfo({(float)width, (float)height}, nullptr));
	    wrapperFrame.::UiElement::SetSize({(float)width, (float)height});
        UpdateLockCursor();
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
    if(cursorLocked)
    {
        UpdateLockCursor();
        ClipCursor(&lockCursorRegion);
    }


    UpdateGlobalInputState();
    //Notify that update happened
    wrapperFrame.NotifyOnTick();


	if(renderingProvider != nullptr)
	    renderingProvider->Render();

	lock_guard<std::mutex>updateFinishedLock(updateMutex);
    updateFinished = true;
    //CoreWindow::ConsoleWrite("Update finished");
	updateFinishedSignal.notify_all();
    mouseDelta.SetValue(0, 0); //Reset the delta as it is 0
}

void CoreWindow::RedrawWindow()
{
    if(renderingProvider != nullptr)
        renderingProvider->Render();
	UpdateWindow(windowHandle);
}

void CoreWindow::CloseWindow()
{
	PostMessage(windowHandle, WM_CLOSE, NULL, NULL);
}

Window& CoreWindow::GetWrapperFrame()
{
	return wrapperFrame;
}

void CoreWindow::CreateConsole()
{
	AllocConsole();
}

void CoreWindow::ConsoleWrite(string output)
{
	DWORD succWritten;
	output.append("\n");
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output.c_str(), output.size(), &succWritten, NULL);
}

void CoreWindow::UnicodeConsoleWrite(std::wstring output)
{
	DWORD succWritten;
	output.append(L"\n");
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), output.c_str(), output.size(), &succWritten, NULL);
}

void CoreWindow::UpdateScale()
{
	SetWindowPos(windowHandle, NULL, wrapperFrame.GetX(), wrapperFrame.GetY(), wrapperFrame.GetWidth(), wrapperFrame.GetHeight(), SWP_SHOWWINDOW | SWP_DRAWFRAME);
}

CoreWindow::CoreWindow(ApplicationController::WinEntryArgs &args, Window& wrapperFrame, string windowName, LONG style) : wrapperFrame(wrapperFrame), renderBehavior(*this)
{
	//Arguments
	hInstance = args.hInstance;
	HINSTANCE hPrevInstance = args.hPrevInstance;
	LPSTR lpCmdLine = args.lpCmdLine;
	int nCmdShow = args.nCmdShow;

	CreateConsole();
	WNDCLASS* windowInfo = new WNDCLASS;
	memset(windowInfo, 0, sizeof(WNDCLASS));
	windowInfo->style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowInfo->lpfnWndProc = (WNDPROC)ApplicationController::WindowProc;
	windowInfo->cbClsExtra = NULL;
	windowInfo->cbWndExtra = NULL;
	windowInfo->hInstance = hInstance;
	windowInfo->hIcon = NULL;
	windowInfo->hCursor = LoadCursor(NULL, IDC_ARROW);
	windowInfo->hbrBackground = NULL;
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
		ConsoleWrite("Error creating window handle " + to_string(GetLastError()));
		system("PAUSE");
		exit(0);
	}
	SetWindowLongPtr(windowHandle, USER_DATA, (LONG_PTR)this);
	fpsTimer.SetInterval(1000/targetFps);
	fpsTimer.SetPeriodic(false);

	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);

	//Critical Section end
}


HWND CoreWindow::GetWindowHandle()
{
	return windowHandle;
}

CoreWindow::~CoreWindow()
{
    ClipCursor(NULL);
}

void CoreWindow::Repaint()
{
	RedrawWindow();
}

void CoreWindow::AddRenderable(RenderCommander &renderable)
{
	renderBehavior.AddRenderable(renderable);
}

void CoreWindow::RemoveRenderable(RenderCommander& renderable)
{
	renderBehavior.RemoveRenderable(renderable);
}

std::vector<std::reference_wrapper<RenderCommander>> CoreWindow::GetRenderables()
{
	return renderBehavior.GetRenderables();
}


void CoreWindow::OnRender(RenderEventInfo e)
{
    //Wait for on sync to finish before returning the call.
    //The reason why is because we want to capture the current snapshot of the draw state and then draw the complete data.
    //During the sync we can't end up in a case where the data is changed.
    /*if(renderingProvider != nullptr)
        renderingProvider->Render();*/
}

void CoreWindow::AddOnResizePreProcessSubsriber(ResizeSubscriber &subscriber)
{
    preProcessSubject.AddOnResizeSubscriber(subscriber);
}

RenderingProvider *CoreWindow::GetRenderingProvider()
{
    return renderingProvider;
}

void CoreWindow::SetRenderingProvider(RenderingProvider& provider)
{
    this->renderingProvider = &provider;
}

void CoreWindow::RemoveOnResizePreProcessSubsriber(ResizeSubscriber &subscriber)
{
    preProcessSubject.RemoveOnResizeSubscriber(subscriber);
}

void CoreWindow::OnSync(const DrawData &data)
{
    //No sync data here
}

void CoreWindow::WaitForUpdateToFinish()
{
//    if(!updateFinished)
//        CoreWindow::ConsoleWrite("Waiting for update to finish");
//    else
//        CoreWindow::ConsoleWrite("No update, continuing");
    std::unique_lock<std::mutex>updateFinishedLock(updateMutex);
    updateFinishedSignal.wait(updateFinishedLock, [=]{return updateFinished;});
}


void CoreWindow::RecieveMessage(const MSG &msg)
{
    PostThreadMessageA(updateThreadId, msg.message, msg.wParam, msg.lParam);
}

void CoreWindow::RecieveMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    MSG currentMsg = {NULL, uMsg, wParam, lParam};
    RecieveMessage(currentMsg);
}

bool CoreWindow::IsEventBased() const
{
    return eventBased;
}

void CoreWindow::SetEventBased(bool eventBased)
{
    CoreWindow::eventBased = eventBased;
}

void CoreWindow::UpdateGlobalInputState()
{
    BYTE keyboardState[256];
    bool state = GetKeyboardState(keyboardState);
    InputManager::globalInput->SetKeyboardState(keyboardState);
    InputManager::globalInput->SetMousePosition(mousePos);
    InputManager::globalInput->SetMouseDeltaPosition(mouseDelta);
}

void CoreWindow::SetLockCursorSize(const Vector2& size)
{
    lockCursorSize = size;
}

void CoreWindow::UpdateLockCursor()
{
    if (cursorLocked == false)
        return;

    //Calculate the center of the wrapper frame
    lockCursorRegion.left = (wrapperFrame.GetX() + wrapperFrame.GetWidth() / 2);
    lockCursorRegion.top = (wrapperFrame.GetY() + wrapperFrame.GetHeight() / 2);
    lockCursorRegion.right = (wrapperFrame.GetX() + wrapperFrame.GetWidth() / 2);
    lockCursorRegion.bottom = (wrapperFrame.GetY() + wrapperFrame.GetHeight() / 2);

    //Find the collision. Each time the mouse collides, reset it to the center. Mouse can move 1 pixel in any direction.
    //The single pixel determines how much to add towards the delta.
    //Also create a strategy for various mouse inputs.
    lockCursorRegion.left -= lockCursorSize.GetX() / 2;
    lockCursorRegion.top -= lockCursorSize.GetY() / 2;
    lockCursorRegion.right += lockCursorSize.GetX() / 2;
    lockCursorRegion.bottom += lockCursorSize.GetY() / 2;
}

void CoreWindow::LockCursor(const bool &lockState)
{
    if(lockState == false)
        ClipCursor(NULL);
    cursorLocked = lockState;
}

const bool &CoreWindow::IsCursorLocked() const
{
    return cursorLocked;
}

void CoreWindow::MsgSubject::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    for(ResizeSubscriber& subscriber : resizeSubscribers)
        subscriber.OnResize(event);

}

void CoreWindow::MsgSubject::AddOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizeSubscribers.emplace_back(subscriber);
}

void CoreWindow::MsgSubject::RemoveOnResizeSubscriber(ResizeSubscriber &subscriber)
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
