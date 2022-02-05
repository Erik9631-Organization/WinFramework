#include "Window.h"
#include "CoreWindow.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ApplicationController.h"
#include <string>
#include "EventResizeInfo.h"
#include "EventMouseStateInfo.h"
#include "EventKeyStateInfo.h"
#include "GdiRenderingProvider.h"

using namespace std;

void Window::CreateCoreWindow(LONG style)
{
	mutex windowInit;
	windowThread = new thread([=]
	{
		ApplicationController::WinEntryArgs args = ApplicationController::GetWinEntryArgs();
		coreFrame = new CoreWindow(args , *this, name, style);
		CoreWindow::ConsoleWrite("Construction complete");
		initNotified = true;
		initWait->notify_one();
		ApplicationController::SubscribeToWinProc(*coreFrame); //Not subscription. This is only the callback where all the messages from the windows are processed.
		coreFrame->MessageLoop();
	});
	ApplicationController::AddThread(windowThread);
	unique_lock<mutex>lock(windowInit);
	initWait->wait(lock, [=] {return initNotified; });
	SetRenderingProvider(make_shared<GdiRenderingProvider>());
	CoreWindow::ConsoleWrite("Init done");
	initDone = true;
}


void Window::AddWindowStyle(LONG styleFlags)
{
	coreFrame->SetWindowAttributes(GWL_STYLE, styleFlags);
}

void Window::RemoveWindowStyle(LONG styleFlags)
{
	coreFrame->RemoveWindowAttributes(GWL_STYLE, styleFlags);
}

void Window::AddWindowExtendedStyle(LONG styleFlags)
{
	coreFrame->SetWindowAttributes(GWL_EXSTYLE, styleFlags);
}

void Window::RemoveWindowExtendedStyle(LONG styleFlags)
{
	coreFrame->RemoveWindowAttributes(GWL_EXSTYLE, styleFlags);
}

void Window::SetSize(float width, float height)
{
	UiElement::SetSize(width, height);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void Window::SetSize(Vector2 size)
{
	UiElement::SetSize(size);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void Window::Repaint()
{
	if(coreFrame != nullptr)
		coreFrame->RedrawWindow();
}

void Window::NotifyOnMouseDown(EventMouseStateInfo e)
{
	UiElement::NotifyOnMouseDown(e);
	UiElement* result = std::any_cast<UiElement*>(ColidesWithUpmost(e.GetMouseAbsolutePosition()));

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

void Window::SetPosition(float x, float y)
{
	UiElement::SetPosition(x, y);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void Window::SetPosition(Vector2 point)
{
	UiElement::SetPosition(point);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void Window::NotifyOnKeyDown(EventKeyStateInfo e)
{
	UiElement::NotifyOnKeyDown(EventKeyStateInfo(this, e));
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyDown(EventKeyStateInfo(currentFocus, e));
}

void Window::NotifyOnKeyUp(EventKeyStateInfo e)
{
	UiElement::NotifyOnKeyUp(EventKeyStateInfo(this, e));
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyUp(EventKeyStateInfo(currentFocus, e));
}

void Window::NotifyOnKeyPressed(EventKeyStateInfo e)
{
	UiElement::NotifyOnKeyPressed(EventKeyStateInfo(this, e));
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyPressed(EventKeyStateInfo(currentFocus, e));
}

void Window::CloseWindow()
{
	if (coreFrame != nullptr)
		coreFrame->CloseWindow();
}

void Window::UpdateWindow()
{
	if(coreFrame != nullptr)
		coreFrame->RedrawWindow();
}

Window::Window(string windowName) : Window(800, 600, 800, 600, windowName)
{

}

Window::Window(int x, int y, int width, int height, string windowName) : Window(x, y, width, height, windowName, WS_OVERLAPPEDWINDOW)
{

}


Window::Window(int x, int y, int width, int height, string windowName, LONG style) : UiElement(x, y, width, height, windowName)
{
	initWait = new condition_variable();
	componentType = "Window";
	CreateCoreWindow(style);
	coreFrame->RedrawWindow();
	background.SetColor({255, 255, 255});
	AddRenderable(background);
}

void Window::Add(UiElement & component)
{
	UiElement::Add(component);
}

Window::~Window()
{
    renderingProvider->OnDestroy(*coreFrame);
	delete coreFrame;
	delete initWait;
}

void Window::NotifyOnMouseHover(EventMouseStateInfo e)
{
    UiElement::NotifyOnMouseHover(e);
    if(currentCapture != nullptr)
        currentCapture->NotifyOnMouseCapture(e);
}

void Window::NotifyOnMouseUp(EventMouseStateInfo e)
{
    UiElement::NotifyOnMouseUp(e);
    if(currentCapture == nullptr)
        return;
    currentCapture->SetMouseCaptured(false);
    currentCapture = nullptr;

}

void Window::SetRenderingProvider(RenderingProvider &provider)
{
    if(coreFrame == nullptr)
        return;
    renderingProvider->OnRemove(*coreFrame);
    coreFrame->SetRenderingProvider(provider);
}

RenderingProvider *Window::GetRenderingProvider()
{
    if(coreFrame != nullptr)
        return coreFrame->GetRenderingProvider();
    return nullptr;
}

void Window::SetRenderingProvider(std::shared_ptr<RenderingProvider> renderingProvider)
{
    if(coreFrame == nullptr)
        return;
    if(this->renderingProvider != nullptr)
        this->renderingProvider->OnRemove(*coreFrame);

    this->renderingProvider = renderingProvider;
    renderingProvider->OnInit(*coreFrame);
}
