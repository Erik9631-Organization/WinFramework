#include "WindowFrame.h"
#include "CoreWindowFrame.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ApplicationController.h"
#include <string>
using namespace std;

void WindowFrame::CreateCoreWindow(int x, int y, int width, int height, string windowName)
{
	mutex windowInit;
	condition_variable* var = new condition_variable();

	thread windowThread([=]
	{
		ApplicationController::WinEntryArgs args = ApplicationController::GetWinEntryArgs();
		coreFrame = new CoreWindowFrame(args, *var, this, windowName);
		ApplicationController::SubscribeToMessageLoop(coreFrame);
		SetPosition(x, y);
		SetSize(width, height);
		coreFrame->MessageLoop();
	}); 
	windowThread.detach();
	unique_lock<mutex>lock(windowInit);
	var->wait(lock);
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

	AddOnAddListener(this);
	OnAdd(*this);
	coreFrame->RedrawWindow();

}

WindowFrame::WindowFrame(int x, int y, int width, int height, string windowName)
{
	CreateCoreWindow(x, y, width, height, windowName);
	componentName = "WindowFrame";
	coreFrame->RedrawWindow();
}

WindowFrame::~WindowFrame()
{
}

void WindowFrame::OnAdd(Component & component)
{
	CoreWindowFrame::ConsoleWrite("Component added: " + component.GetComponentType());
	coreFrame->ComponentAdded(component);
	UpdateWindow();
}
