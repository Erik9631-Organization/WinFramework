#include "WindowFrame.h"
#include "CoreWindowFrame.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ApplicationController.h"
#include <string>
using namespace std;
condition_variable WindowFrame::initWait;
bool WindowFrame::initNotified = false;

void WindowFrame::CreateCoreWindow(int x, int y, int width, int height, string windowName)
{
	mutex windowInit;

	thread windowThread([=]
	{
		ApplicationController::WinEntryArgs args = ApplicationController::GetWinEntryArgs();
		coreFrame = new CoreWindowFrame(args , *this, windowName);
		CoreWindowFrame::ConsoleWrite("Construction complete");
		initNotified = true;
		initWait.notify_all();
		ApplicationController::SubscribeToMessageLoop(*coreFrame); //Not subscription. This is only the callback where all the messages from the windows are processed.
		coreFrame->MessageLoop();
	}); 
	windowThread.detach();
	unique_lock<mutex>lock(windowInit);
	initWait.wait(lock, [=] {return initNotified; });
	coreFrame->ComponentAdded(*this);
	SetPosition(x, y);
	SetSize(width, height);
	CoreWindowFrame::ConsoleWrite("Init done");
}


void WindowFrame::SetSize(int width, int height)
{
	Component::SetSize(width, height);
	coreFrame->SetSize(width, height);
}

void WindowFrame::SetSize(Size size)
{
	Component::SetSize(size);
	coreFrame->SetSize(size.Width, size.Height);
}

void WindowFrame::SetPosition(int x, int y)
{
	Component::SetPosition(x, y);
	coreFrame->SetPosition(x, y);
}

void WindowFrame::SetPosition(Point point)
{
	Component::SetPosition(point);
	coreFrame->SetPosition(point.X, point.Y);
}

void WindowFrame::UpdateWindow()
{	
	coreFrame->RedrawWindow();
}

void WindowFrame::Paint(Graphics& graphics)
{
	Component::Paint(graphics);
	graphics.Clear(Color(255, 255, 255));
}

WindowFrame::WindowFrame(string windowName) : Component()
{
	CreateCoreWindow(0, 0, 800, 600, windowName);
	componentName = "Window";
	coreFrame->RedrawWindow();

}

WindowFrame::WindowFrame(int x, int y, int width, int height, string windowName)
{
	CreateCoreWindow(x, y, width, height, windowName);
	componentName = "WindowFrame";
	coreFrame->RedrawWindow();
}

void WindowFrame::Add(Component & component)
{
	Component::Add(component);
	coreFrame->ComponentAdded(component);
}

WindowFrame::~WindowFrame()
{
	delete coreFrame;
}