#include "WindowsCore.h"
#include <Windows.h>
#include <iostream>
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
#include "WindowsCoreArgs.h"

#if defined(_M_X64)
#define USER_DATA (GWLP_USERDATA)
#else
#define USER_DATA (GWL_USERDATA)
#endif

HDC windowHdc;
using namespace std;
using namespace chrono;

void WindowsCore::WindowsMessageLoop()
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
    delete wrapperFrame;
}
void WindowsCore::ProcessKeyState(UINT msg, WPARAM wParam, LPARAM lParam)
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
            NotifyCoreOnKeyDown(EventKeyStateInfo(nullptr, wParam, unicodeKey, keyboardState));
		else
			NotifyCoreOnKeyPressed(EventKeyStateInfo(nullptr, wParam, unicodeKey, keyboardState));
	}
	else if(msg == WM_KEYUP)
		NotifyCoreOnKeyDown(EventKeyStateInfo(nullptr, wParam, unicodeKey, keyboardState));
}

long long int WindowsCore::SetAttributes(int index, long long int parameter)
{
	LONG currentAttributes = GetWindowLong(windowHandle, index);
	LONG newAttributes = currentAttributes | parameter;
	LONG returnVal = SetWindowLong(windowHandle, index, newAttributes);
	SetWindowPos(windowHandle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	return returnVal;
}

long long int WindowsCore::RemoveAttribute(int index, long long int parameter)
{
	LONG currentAttributes = GetWindowLong(windowHandle, index);
	LONG newAttributes = currentAttributes & (~parameter);
	LONG returnVal = SetWindowLong(windowHandle, index, newAttributes);
	SetWindowPos(windowHandle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	return returnVal;
}

void WindowsCore::ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
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
        if(!UnregisterClassA(wrapperFrame->GetComponentName().c_str(), hInstance))
            ConsoleWrite("UnRegister Class error: " + to_string(GetLastError()));
        processMessages = false;
        return;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOVE:
    {
        Vector2 pos = {(float)*((unsigned short*)&lParam), (float)((unsigned short*)&lParam)[1]};
        EventMoveInfo e = {pos, nullptr};
        NotifyCoreOnMove(e);
        //wrapperFrame.::UiElement::SetPosition({(float)*((unsigned short*)&lParam), (float)((unsigned short*)&lParam)[1]});
        UpdateLockCursor();
        break;
    }
	case WM_SIZE:
	{
	    unsigned short width = ((unsigned short*)&lParam)[0];
	    unsigned short height = ((unsigned short*)&lParam)[1];
        EventResizeInfo e = EventResizeInfo{{(float)width, (float)height}, nullptr};
	    preProcessSubject.NotifyOnResizeSubscribers(e);
        NotifyCoreOnResize(e);
	    //wrapperFrame.::UiElement::SetSize({(float)width, (float)height});
        UpdateLockCursor();
	    break;
	}
	case WM_MOUSEMOVE:
	    prevMousePos = mousePos;
        mousePos.SetX(((unsigned short*)&lParam)[0]);
        mousePos.SetY(((unsigned short*)&lParam)[1]);

        mouseDelta = mousePos - prevMousePos;
        //relativePos = mousePos - wrapperFrame.GetPosition();
        NotifyCoreOnMouseMove(EventMouseStateInfo(mousePos, mousePos, mouseDelta, 0, wrapperFrame));
		break;
	case WM_LBUTTONDOWN:
        NotifyCoreOnMouseLButtonDown(EventMouseStateInfo(mousePos, relativePos, mouseDelta, wParam, wrapperFrame));
		break;
	case WM_LBUTTONUP:
        NotifyCoreOnMouseLButtonUp(EventMouseStateInfo(mousePos, relativePos, mouseDelta, wParam, wrapperFrame));
		break;
	case WM_LBUTTONDBLCLK:
	    NotifyCoreOnMousePressed(EventMouseStateInfo(mousePos, relativePos, mouseDelta, wParam, wrapperFrame));
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
    wrapperFrame->NotifyOnTick();


	if(renderingProvider != nullptr)
	    renderingProvider->Render();

	lock_guard<std::mutex>updateFinishedLock(updateMutex);
    updateFinished = true;
    //CoreWindow::ConsoleWrite("Update finished");
	updateFinishedSignal.notify_all();
    mouseDelta.SetValue(0, 0); //Reset the delta as it is 0
}

void WindowsCore::Redraw()
{
    if(renderingProvider != nullptr)
        renderingProvider->Render();
	UpdateWindow(windowHandle);
}

void WindowsCore::Close()
{
	PostMessage(windowHandle, WM_CLOSE, NULL, NULL);
}

Window * WindowsCore::GetWrapperFrame()
{
	return wrapperFrame;
}

void WindowsCore::CreateConsole()
{
	AllocConsole();
}

void WindowsCore::ConsoleWrite(string output)
{
	DWORD succWritten;
	output.append("\n");
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), output.c_str(), output.size(), &succWritten, NULL);
}

void WindowsCore::UnicodeConsoleWrite(std::wstring output)
{
	DWORD succWritten;
	output.append(L"\n");
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), output.c_str(), output.size(), &succWritten, NULL);
}

void WindowsCore::UpdateScale()
{
	SetWindowPos(windowHandle, NULL, wrapperFrame->GetX(), wrapperFrame->GetY(), wrapperFrame->GetWidth(), wrapperFrame->GetHeight(), SWP_SHOWWINDOW | SWP_DRAWFRAME);
}

WindowsCore::WindowsCore(Window *wrapperFrame, const string &windowName, LONG style) : wrapperFrame(wrapperFrame), renderBehavior(*this)
{
    this->windowName = windowName;
    this->style = style;
}

void WindowsCore::CreateWinApiWindow()
{
    //Arguments
    hInstance = GetModuleHandleA(NULL);

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
    windowHandle = CreateWindow(windowInfo->lpszClassName, windowInfo->lpszClassName, style, wrapperFrame->GetX(),
                                wrapperFrame->GetY(), wrapperFrame->GetWidth(), wrapperFrame->GetHeight(), NULL, NULL, hInstance, NULL);

    if (!windowHandle)
    {
        ConsoleWrite("Error creating window handle " + to_string(GetLastError()));
        system("PAUSE");
        exit(0);
    }
    SetWindowLongPtr(windowHandle, USER_DATA, (LONG_PTR)this);
    fpsTimer.SetInterval(1000/targetFps);
    fpsTimer.SetPeriodic(false);
    coreSubscribers.emplace_back(&coreAdapter);

    ShowWindow(windowHandle, SW_SHOW);
    UpdateWindow(windowHandle);

    //Critical Section end
}



HWND WindowsCore::GetWindowHandle()
{
	return windowHandle;
}

WindowsCore::~WindowsCore()
{
    ClipCursor(NULL);
}

void WindowsCore::Repaint()
{
    Redraw();
}

void WindowsCore::AddRenderCommander(RenderCommander &renderable)
{
    renderBehavior.AddRenderCommander(renderable);
}

void WindowsCore::RemoveRenderCommander(RenderCommander& renderable)
{
    renderBehavior.RemoveRenderCommander(renderable);
}

std::vector<std::reference_wrapper<RenderCommander>> WindowsCore::GetRenderables()
{
	return renderBehavior.GetRenderables();
}


void WindowsCore::OnRenderSync(RenderEventInfo e)
{
    //Wait for on sync to finish before returning the call.
    //The reason why is because we want to capture the current snapshot of the draw state and then draw the complete data.
    //During the sync we can't end up in a case where the data is changed.
    /*if(renderingProvider != nullptr)
        renderingProvider->Render();*/
}

void WindowsCore::AddOnResizePreProcessSubsriber(ResizeSubscriber &subscriber)
{
    preProcessSubject.AddOnResizeSubscriber(subscriber);
}

RenderingProvider *WindowsCore::GetRenderingProvider()
{
    return renderingProvider;
}

void WindowsCore::SetRenderingProvider(RenderingProvider& provider)
{
    this->renderingProvider = &provider;
}

void WindowsCore::RemoveOnResizePreProcessSubsriber(ResizeSubscriber &subscriber)
{
    preProcessSubject.RemoveOnResizeSubscriber(subscriber);
}

void WindowsCore::OnSync(const DrawData &data)
{
    //No sync data here
}

void WindowsCore::WaitForUpdateToFinish()
{
//    if(!updateFinished)
//        CoreWindow::ConsoleWrite("Waiting for update to finish");
//    else
//        CoreWindow::ConsoleWrite("No update, continuing");
    std::unique_lock<std::mutex>updateFinishedLock(updateMutex);
    updateFinishedSignal.wait(updateFinishedLock, [=]{return updateFinished;});
}


bool WindowsCore::IsEventBased() const
{
    return eventBased;
}

void WindowsCore::SetEventBased(bool eventBased)
{
    WindowsCore::eventBased = eventBased;
}

void WindowsCore::UpdateGlobalInputState()
{
    BYTE keyboardState[256];
    bool state = GetKeyboardState(keyboardState);
    InputManager::globalInput->SetKeyboardState(keyboardState);
    InputManager::globalInput->SetMousePosition(mousePos);
    InputManager::globalInput->SetMouseDeltaPosition(mouseDelta);
}

void WindowsCore::SetLockCursorSize(const Vector2& size)
{
    lockCursorSize = size;
}

void WindowsCore::UpdateLockCursor()
{
    if (cursorLocked == false)
        return;

    //Calculate the center of the wrapper frame
    lockCursorRegion.left = (wrapperFrame->GetX() + wrapperFrame->GetWidth() / 2);
    lockCursorRegion.top = (wrapperFrame->GetY() + wrapperFrame->GetHeight() / 2);
    lockCursorRegion.right = (wrapperFrame->GetX() + wrapperFrame->GetWidth() / 2);
    lockCursorRegion.bottom = (wrapperFrame->GetY() + wrapperFrame->GetHeight() / 2);

    //Find the collision. Each time the mouse collides, reset it to the center. Mouse can move 1 pixel in any direction.
    //The single pixel determines how much to add towards the delta.
    //Also create a strategy for various mouse inputs.
    lockCursorRegion.left -= lockCursorSize.GetX() / 2;
    lockCursorRegion.top -= lockCursorSize.GetY() / 2;
    lockCursorRegion.right += lockCursorSize.GetX() / 2;
    lockCursorRegion.bottom += lockCursorSize.GetY() / 2;
}

void WindowsCore::LockCursor(const bool &lockState)
{
    if(lockState == false)
        ClipCursor(NULL);
    cursorLocked = lockState;
}

const bool &WindowsCore::IsCursorLocked() const
{
    return cursorLocked;
}

void WindowsCore::NotifyCoreOnDestroy(std::any src)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnDestroy(src);
}

void WindowsCore::NotifyCoreOnClose(std::any src)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnClose(src);
}

void WindowsCore::NotifyCoreOnMove(EventMoveInfo e)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnMove(e);
}

void WindowsCore::NotifyCoreOnResize(EventResizeInfo e)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnResize(e);
}

void WindowsCore::NotifyCoreOnMouseMove(EventMouseStateInfo e)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnMouseMove(e);
}

void WindowsCore::NotifyCoreOnMouseLButtonDown(EventMouseStateInfo e)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnMouseLButtonDown(e);
}

void WindowsCore::NotifyCoreOnMouseLButtonUp(EventMouseStateInfo e)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnMouseLButtonUp(e);
}

void WindowsCore::NotifyCoreOnKeyUp(EventKeyStateInfo e)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnKeyUp(e);
}

void WindowsCore::NotifyCoreOnKeyDown(EventKeyStateInfo e)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnKeyDown(e);
}

void WindowsCore::NotifyCoreOnKeyPressed(EventKeyStateInfo e)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnKeyPressed(e);
}


void WindowsCore::NotifyCoreOnWheelMoved(EventKeyStateInfo e)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnWheelMoved(e);
}

void WindowsCore::NotifyCoreOnMousePressed(EventMouseStateInfo e)
{
    for(auto subscriber : coreSubscribers)
        subscriber->CoreOnMousePressed(e);
}


void WindowsCore::AddCoreSubscriber(CoreSubscriber *subscriber)
{
    coreSubscribers.emplace_back(subscriber);
}

void WindowsCore::RemoveCoreSubscriber(CoreSubscriber *subscriber)
{
    for(auto iterator = coreSubscribers.begin(); iterator != coreSubscribers.end(); iterator++)
    {
        if(*iterator == subscriber)
        {
            coreSubscribers.erase(iterator);
            return;
        }
    }
}

void WindowsCore::Start()
{
    bool initSignal = false;
    mutex initLock;
    auto initCondition = new std::condition_variable();
    updateThread = &ApplicationController::GetApplicationController()->CreateThread([&]{
        CreateWinApiWindow();
        initSignal = true;
        std::unique_lock<mutex> lock{initLock};
        initCondition->notify_one();
        lock.unlock();
        WindowsMessageLoop();
    },to_string((long long) this)+"window");
    std::unique_lock<mutex> lock{initLock};
    initCondition->wait(lock, [&]{return initSignal;});
}
//
//std::unique_ptr<WindowsCore> WindowsCore::Create(Window *wrapperFrame, const string& windowName, LONG style)
//{
//    auto coreInstance = new WindowsCore(wrapperFrame, windowName, style);
//    auto window = std::unique_ptr<WindowsCore>(coreInstance);
//    window->Start();
//    return std::move(window);
//}

unique_ptr<Core> WindowsCore::Create(Window *window, std::any args)
{
    auto inputArgs = std::any_cast<WindowsCoreArgs>(args);
    auto core = new WindowsCore(window, inputArgs.name, inputArgs.style);
    auto corePtr = std::unique_ptr<WindowsCore>(core);
    corePtr->Start();
    return std::move(corePtr);
}

void WindowsCore::SetWindow(Window *window)
{
    this->wrapperFrame = window;
}


void WindowsCore::MsgSubject::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    for(ResizeSubscriber& subscriber : resizeSubscribers)
        subscriber.OnResize(event);

}

void WindowsCore::MsgSubject::AddOnResizeSubscriber(ResizeSubscriber &subscriber)
{
    resizeSubscribers.emplace_back(subscriber);
}

void WindowsCore::MsgSubject::RemoveOnResizeSubscriber(ResizeSubscriber &subscriber)
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