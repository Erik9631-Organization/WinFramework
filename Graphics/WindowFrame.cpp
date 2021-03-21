#include "WindowFrame.h"
#include "CoreWindowFrame.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ApplicationController.h"
#include <string>
#include "EventResizeInfo.h"
#include "EventMouseStateInfo.h"
#include "EventKeyStateInfo.h"

using namespace std;

void WindowFrame::CreateCoreWindow()
{
	mutex windowInit;

	windowThread = new thread([=]
	{
		ApplicationController::WinEntryArgs args = ApplicationController::GetWinEntryArgs();
		coreFrame = new CoreWindowFrame(args , *this, name);
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


void WindowFrame::SetSize(int width, int height)
{
	Component::SetSize(width, height);
}

void WindowFrame::SetSize(Size size)
{
	Component::SetSize(size);
}

void WindowFrame::Repaint()
{
	if(coreFrame != nullptr)
		coreFrame->RedrawWindow();
}

void WindowFrame::NotifyOnMouseDown(EventMouseStateInfo e)
{
	Component::NotifyOnMouseDown(e);
	Component* result = std::any_cast<Component*>(ColidesWithUpmost(e.GetMousePosition()));
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
}

void WindowFrame::SetPosition(Point point)
{
	Component::SetPosition(point);
}

void WindowFrame::NotifyOnKeyDown(EventKeyStateInfo e)
{
	Component::NotifyOnKeyDown(e);
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyDown(e);
}

void WindowFrame::NotifyOnKeyUp(EventKeyStateInfo e)
{
	Component::NotifyOnKeyUp(e);
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyUp(e);
}

void WindowFrame::NotifyOnKeyPressed(EventKeyStateInfo e)
{
	Component::NotifyOnKeyPressed(e);
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyPressed(e);
}

void WindowFrame::UpdateWindow()
{
	if(coreFrame != nullptr)
		coreFrame->RedrawWindow();
}

WindowFrame::WindowFrame(string windowName) : WindowFrame(800, 600, 800, 600, windowName)
{

}

WindowFrame::WindowFrame(int x, int y, int width, int height, string windowName) : Component(x, y, width, height, windowName)
{
	initWait = new condition_variable();
	componentType = "Window";
	CreateCoreWindow();
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
