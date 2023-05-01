#include "WindowsCore.h"
#include <iostream>
#include "EventResizeInfo.h"
#include "RenderEventInfo.h"
#include "EventMouseStateInfo.h"
#include "EventKeyStateInfo.h"
#include "Renderer.h"
#include <processthreadsapi.h>
#include "Messages.h"
#include <chrono>
#include "CoreArgs.h"

#if defined(_M_X64)
#define USER_DATA (GWLP_USERDATA)
#else
#define USER_DATA (GWL_USERDATA)
#endif

HDC windowHdc;
using namespace std;
using namespace chrono;


LRESULT WindowsCore::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WindowsCore* frame = reinterpret_cast<WindowsCore*>(GetWindowLongPtr(hwnd, USER_DATA));
    if (frame != nullptr)
        frame->ProcessMessage(uMsg, wParam, lParam);

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


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
	PAINTSTRUCT paintInfo;

	switch (msg)
	{
	case WM_CLOSE:
        DestroyWindow(windowHandle);
        if(!UnregisterClassA(this->windowName.c_str(), hInstance))
            cout << "UnRegister Class error: " << GetLastError() << endl;
        processMessages = false;
        renderer->OnDestroy(*this);
        return;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOVE:
    {
        auto pos = glm::vec4((float)*((unsigned short*)&lParam), (float)((unsigned short*)&lParam)[1], 0, 0);
        //TODO use separate event for core
        EventMoveInfo e = {pos, pos, nullptr};
        NotifyCoreOnMove(e);
        //wrapperFrame.::UiElement::SetPosition({(float)*((unsigned short*)&lParam), (float)((unsigned short*)&lParam)[1]});
        UpdateLockCursor();
        break;
    }
	case WM_SIZE:
	{
	    unsigned short width = ((unsigned short*)&lParam)[0];
	    unsigned short height = ((unsigned short*)&lParam)[1];
        if(renderer != nullptr)
            renderer->SetViewPortSize(width, height);
        EventResizeInfo e = EventResizeInfo{{(float)width, (float)height, 0}, nullptr};
	    preProcessSubject.NotifyOnResizeSubscribers(e);
        NotifyCoreOnResize(e);
	    //wrapperFrame.::UiElement::SetSize({(float)width, (float)height});
        UpdateLockCursor();
	    break;
	}
	case WM_MOUSEMOVE:
	    prevMousePos = mousePos;
        mousePos.x = ((unsigned short*)&lParam)[0];
        mousePos.y = ((unsigned short*)&lParam)[1];

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
    case REDRAW_MESSAGE:
        if(renderer != nullptr)
            renderer->SwapScreenBuffer();

	}
    if(cursorLocked)
    {
        UpdateLockCursor();
        ClipCursor(&lockCursorRegion);
    }

    //If redraw falg is set then redraw


    UpdateGlobalInputState();
    //Notify that update happened
    wrapperFrame->NotifyOnTick();

	lock_guard<std::mutex>updateFinishedLock(updateMutex);
    updateFinished = true;
    //CoreWindow::ConsoleWrite("Update finished");
	updateFinishedSignal.notify_all();
//    if(renderer != nullptr)
//        renderer->SwapScreenBuffer();
    //ResetSize the delta as it is 0
    mouseDelta.x = 0;
    mouseDelta.y = 0;
}

void WindowsCore::ScheduleRedraw()
{
    //If call comes from the same thread as the one that is processing messages then schedule a redraw else redraw immidiatelly
    PostMessageA(windowHandle, REDRAW_MESSAGE, 0, 0);
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

void WindowsCore::UpdateScale()
{
    if(wrapperFrame == nullptr)
        return;
	SetWindowPos(windowHandle, NULL, wrapperFrame->GetPosition().x,
                 wrapperFrame->GetPosition().y,
                 wrapperFrame->GetSize().x,
                 wrapperFrame->GetSize().y, SWP_SHOWWINDOW | SWP_DRAWFRAME);
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
    windowInfo->lpfnWndProc = (WNDPROC)WindowsCore::WindowProc;
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
        std::cout << "Register Class error: " << GetLastError() << std::endl;
        system("PAUSE");
        exit(0);
    }
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    if(wrapperFrame != nullptr)
    {
        x = (int)wrapperFrame->GetPosition().x;
        y = (int)wrapperFrame->GetPosition().y;
        width = (int)wrapperFrame->GetSize().x;
        height = (int)wrapperFrame->GetSize().y;
    }
    windowHandle = CreateWindow(windowInfo->lpszClassName, windowInfo->lpszClassName, style, x,
                                y, width, height, NULL, NULL, hInstance, NULL);

    if (!windowHandle)
    {
        std::cout << "Error creating window handle " << GetLastError() << endl;
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
    ScheduleRedraw();
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
    /*if(renderer != nullptr)
        renderer->Render();*/
}

void WindowsCore::AddOnResizePreProcessSubsriber(ResizeSubscriber &subscriber)
{
    preProcessSubject.AddOnResizeSubscriber(subscriber);
}

AsyncRenderCommandHandler * WindowsCore::GetRenderer()
{
    return renderer.get();
}

void WindowsCore::SetRenderer(unique_ptr<AsyncRenderCommandHandler> provider)
{
    renderer = std::move(provider);
    renderer->OnInit(*this);
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

void WindowsCore::SetLockCursorSize(const glm::vec3 &size)
{
    lockCursorSize = size;
}

void WindowsCore::UpdateLockCursor()
{
    if (cursorLocked == false)
        return;
    if(wrapperFrame == nullptr)
        return;
    cout << "after for" << endl;
    //Calculate the center of the wrapper frame
    lockCursorRegion.left = (wrapperFrame->GetPosition().x + wrapperFrame->GetSize().x / 2);
    lockCursorRegion.top = (wrapperFrame->GetPosition().y + wrapperFrame->GetSize().y / 2);
    lockCursorRegion.right = (wrapperFrame->GetPosition().x + wrapperFrame->GetSize().x  / 2);
    lockCursorRegion.bottom = (wrapperFrame->GetPosition().y + wrapperFrame->GetSize().y / 2);

    //Find the collision. Each time the mouse collides, reset it to the center. Mouse can move 1 pixel in any direction.
    //The single pixel determines how much to add towards the delta.
    //Also create a strategy for various mouse inputs.
    lockCursorRegion.left -= lockCursorSize.x / 2;
    lockCursorRegion.top -= lockCursorSize.y / 2;
    lockCursorRegion.right += lockCursorSize.x / 2;
    lockCursorRegion.bottom += lockCursorSize.y / 2;
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

unique_ptr<Core> WindowsCore::Create(std::any args)
{
    CoreArgs inputArgs{"window", WS_OVERLAPPEDWINDOW, nullptr};
    if(args.type() == typeid(CoreArgs))
        inputArgs = std::any_cast<CoreArgs>(args);

    auto core = new WindowsCore(inputArgs.associatedWindow, inputArgs.name, WS_OVERLAPPEDWINDOW);
    auto corePtr = std::unique_ptr<WindowsCore>(core);
    corePtr->Start();
    return std::move(corePtr);
}

void WindowsCore::SetWindow(Window *window)
{
    this->wrapperFrame = window;
}

void WindowsCore::ForceRedraw()
{

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
