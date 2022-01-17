#include "WindowFrame.h"
#include "Components/CoreWindowFrame.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Utils/ApplicationController.h"
#include <string>
#include "EventTypes/EventResizeInfo.h"
#include "EventTypes/EventMouseStateInfo.h"
#include "EventTypes/EventKeyStateInfo.h"

using namespace std;

void WindowFrame::CreateCoreWindow(LONG style)
{
	mutex windowInit;

	windowThread = new thread([=]
	{
		ApplicationController::WinEntryArgs args = ApplicationController::GetWinEntryArgs();
		coreFrame = new CoreWindowFrame(args , *this, name, style);
		CoreWindowFrame::ConsoleWrite("Construction complete");
		initNotified = true;
		initWait->notify_one();
		ApplicationController::SubscribeToWinProc(*coreFrame); //Not subscription. This is only the callback where all the messages from the windows are processed.
		coreFrame->MessageLoop();
	});
	ApplicationController::AddThread(windowThread);
	unique_lock<mutex>lock(windowInit);
	initWait->wait(lock, [=] {return initNotified; });
	CoreWindowFrame::ConsoleWrite("Init done");
	initDone = true;
}


void WindowFrame::AddWindowStyle(LONG styleFlags)
{
	coreFrame->SetWindowAttributes(GWL_STYLE, styleFlags);
}

void WindowFrame::RemoveWindowStyle(LONG styleFlags)
{
	coreFrame->RemoveWindowAttributes(GWL_STYLE, styleFlags);
}

void WindowFrame::AddWindowExtendedStyle(LONG styleFlags)
{
	coreFrame->SetWindowAttributes(GWL_EXSTYLE, styleFlags);
}

void WindowFrame::RemoveWindowExtendedStyle(LONG styleFlags)
{
	coreFrame->RemoveWindowAttributes(GWL_EXSTYLE, styleFlags);
}

void WindowFrame::SetSize(int width, int height)
{
	Component::SetSize(width, height);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void WindowFrame::SetSize(Size size)
{
	Component::SetSize(size);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void WindowFrame::Repaint()
{
	if(coreFrame != nullptr)
		coreFrame->RedrawWindow();
}

void WindowFrame::NotifyOnMouseDown(EventMouseStateInfo e)
{
	Component::NotifyOnMouseDown(e);
	Component* result = std::any_cast<Component*>(ColidesWithUpmost(e.GetMouseAbsolutePosition()));

	currentCapture = result;
	//Handle mouse capture
	if(result == nullptr) // Error check
	    return;

	result->NotifyOnMouseCapture(e);

	if (currentFocus == result)
		return;

	if (currentFocus != nullptr)
		currentFocus->SetActive(false);

	result->SetActive(true);
	currentFocus = result;
}

void WindowFrame::SetPosition(int x, int y)
{
	Component::SetPosition(x, y);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void WindowFrame::SetPosition(Point point)
{
	Component::SetPosition(point);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void WindowFrame::NotifyOnKeyDown(EventKeyStateInfo e)
{
	Component::NotifyOnKeyDown(EventKeyStateInfo(this, e));
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyDown(EventKeyStateInfo(currentFocus, e));
}

void WindowFrame::NotifyOnKeyUp(EventKeyStateInfo e)
{
	Component::NotifyOnKeyUp(EventKeyStateInfo(this, e));
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyUp(EventKeyStateInfo(currentFocus, e));
}

void WindowFrame::NotifyOnKeyPressed(EventKeyStateInfo e)
{
	Component::NotifyOnKeyPressed(EventKeyStateInfo(this, e));
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyPressed(EventKeyStateInfo(currentFocus, e));
}

void WindowFrame::CloseWindow()
{
	if (coreFrame != nullptr)
		coreFrame->CloseWindow();
}

void WindowFrame::UpdateWindow()
{
	if(coreFrame != nullptr)
		coreFrame->RedrawWindow();
}

WindowFrame::WindowFrame(string windowName) : WindowFrame(800, 600, 800, 600, windowName)
{

}

WindowFrame::WindowFrame(int x, int y, int width, int height, string windowName) : WindowFrame(x, y, width, height, windowName, WS_OVERLAPPEDWINDOW)
{

}


WindowFrame::WindowFrame(int x, int y, int width, int height, string windowName, LONG style) : Component(x, y, width, height, windowName)
{
	initWait = new condition_variable();
	componentType = "Window";
	CreateCoreWindow(style);
	coreFrame->RedrawWindow();
	background.SetColor(Color::White);
	AddRenderable(background);
}

void WindowFrame::Add(Component & component)
{
	Component::Add(component);
}

WindowFrame::~WindowFrame()
{
	delete coreFrame;
	delete initWait;
}

void WindowFrame::NotifyOnMouseHover(EventMouseStateInfo e)
{
    Component::NotifyOnMouseHover(e);
    if(currentCapture != nullptr)
        currentCapture->NotifyOnMouseCapture(e);
}

void WindowFrame::NotifyOnMouseUp(EventMouseStateInfo e)
{
    Component::NotifyOnMouseUp(e);
    currentCapture = nullptr;
   /* if(currentCapture != nullptr && currentCapture != this) // Shouldn't notify itself
    {
        currentCapture->NotifyOnMouseUp(e);
        currentCapture = nullptr;
    }*/

}
