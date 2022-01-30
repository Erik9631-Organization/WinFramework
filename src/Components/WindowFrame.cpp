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
#include "GdiRenderingProvider.h"

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
	SetRenderingProvider(make_shared<GdiRenderingProvider>());
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

void WindowFrame::SetSize(float width, float height)
{
	UiElement::SetSize(width, height);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void WindowFrame::SetSize(Vector2 size)
{
	UiElement::SetSize(size);
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

void WindowFrame::SetPosition(float x, float y)
{
	UiElement::SetPosition(x, y);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void WindowFrame::SetPosition(Vector2 point)
{
	UiElement::SetPosition(point);
	if (coreFrame != nullptr)
		coreFrame->UpdateScale();
}

void WindowFrame::NotifyOnKeyDown(EventKeyStateInfo e)
{
	UiElement::NotifyOnKeyDown(EventKeyStateInfo(this, e));
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyDown(EventKeyStateInfo(currentFocus, e));
}

void WindowFrame::NotifyOnKeyUp(EventKeyStateInfo e)
{
	UiElement::NotifyOnKeyUp(EventKeyStateInfo(this, e));
	if (currentFocus != nullptr && currentFocus != this)
		currentFocus->NotifyOnKeyUp(EventKeyStateInfo(currentFocus, e));
}

void WindowFrame::NotifyOnKeyPressed(EventKeyStateInfo e)
{
	UiElement::NotifyOnKeyPressed(EventKeyStateInfo(this, e));
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


WindowFrame::WindowFrame(int x, int y, int width, int height, string windowName, LONG style) : UiElement(x, y, width, height, windowName)
{
	initWait = new condition_variable();
	componentType = "Window";
	CreateCoreWindow(style);
	coreFrame->RedrawWindow();
	background.SetColor({255, 255, 255});
	AddRenderable(background);
}

void WindowFrame::Add(UiElement & component)
{
	UiElement::Add(component);
}

WindowFrame::~WindowFrame()
{
	delete coreFrame;
	delete initWait;
}

void WindowFrame::NotifyOnMouseHover(EventMouseStateInfo e)
{
    UiElement::NotifyOnMouseHover(e);
    if(currentCapture != nullptr)
        currentCapture->NotifyOnMouseCapture(e);
}

void WindowFrame::NotifyOnMouseUp(EventMouseStateInfo e)
{
    UiElement::NotifyOnMouseUp(e);
    currentCapture->IsMouseCaptured();
    currentCapture->SetMouseCaptured(false);
    currentCapture = nullptr;

}

void WindowFrame::SetRenderingProvider(RenderingProvider &provider)
{
    if(coreFrame != nullptr)
        coreFrame->SetRenderingProvider(provider);
}

RenderingProvider *WindowFrame::GetRenderingProvider()
{
    if(coreFrame != nullptr)
        return coreFrame->GetRenderingProvider();
    return nullptr;
}

void WindowFrame::SetRenderingProvider(std::shared_ptr<RenderingProvider> renderingProvider)
{
    this->renderingProvider = renderingProvider;
    renderingProvider->OnInit(*coreFrame);
}
