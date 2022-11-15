#include "Window.h"
#include "Core/Windows/WindowsCore.h"
#include <thread>
#include <mutex>
#include "ApplicationController.h"
#include <string>
#include "EventMouseStateInfo.h"
#include "EventKeyStateInfo.h"
#include "GdiRenderingProvider.h"
#include "WindowsCoreArgs.h"
#include "RenderingProviderManager.h"
using namespace std;

void Window::AddWindowStyle(LONG styleFlags)
{
    EventAttributeInfo e = {GWL_STYLE, styleFlags, std::make_any<Presenter*>(this)};
    NotifyOnAttributesChanged(e);
}

void Window::RemoveWindowStyle(LONG styleFlags)
{
    EventAttributeInfo e = {GWL_STYLE, styleFlags, std::make_any<Presenter*>(this)};
    NotifyOnAttributesRemoved(e);
}

void Window::AddWindowExtendedStyle(LONG styleFlags)
{
    EventAttributeInfo e = {GWL_EXSTYLE, styleFlags, std::make_any<Presenter*>(this)};
    NotifyOnAttributesChanged(e);
}

void Window::RemoveWindowExtendedStyle(LONG styleFlags)
{
    EventAttributeInfo e = {GWL_EXSTYLE, styleFlags, std::make_any<Presenter*>(this)};
    NotifyOnAttributesRemoved(e);
}

void Window::SetSize(float width, float height, bool emit)
{
    UiElement::SetSize(width, height, emit);
    if(emit)
        NotifyOnScaleUpdate(std::make_any<Presenter*>(this));
}

void Window::SetSize(Vector2 size, bool emit)
{
    SetSize(size.GetX(), size.GetY(), emit);
}

void Window::Repaint()
{
    NotifyOnRedraw(std::make_any<Window*>(this));
}

void Window::NotifyOnMouseDown(EventMouseStateInfo e)
{
    if(currentFocus != nullptr && currentFocus->IsActive() == false)
    {
        currentFocus = nullptr;
    }


	UiElement::NotifyOnMouseDown(e);
	UiElement* result = std::any_cast<UiElement*>(ColidesWithUpmost(e.GetMouseAbsolutePosition()));

	currentCapture = result;
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

void Window::SetPosition(float x, float y, bool emit)
{
    UiElement::SetPosition(x, y, emit);
    if(emit)
        NotifyOnScaleUpdate(std::make_any<Presenter*>(this));
}

void Window::SetPosition(Vector2 position, bool emit)
{
    SetPosition(position.GetX(), position.GetY(), emit);
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
    NotifyOnClose(std::make_any<Presenter*>(this));
}

void Window::UpdateWindow()
{
    NotifyOnRedraw(std::make_any<Presenter*>(this));
}

Window::Window(string windowName) : Window(800, 600, 800, 600, windowName)
{

}

Window::Window(int x, int y, int width, int height, string windowName) : Window(x, y, width, height, windowName, WS_OVERLAPPEDWINDOW)
{

}

Window::Window(int x, int y, int width, int height, string windowName, LONG style) : UiElement(x, y, width, height, windowName)
{
	componentType = "Window";
	background.SetColor({255, 255, 255});
}

void Window::Add(unique_ptr<UiElement> component)
{
	UiElement::Add(std::move(component));
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

void Window::WaitForSync()
{
    coreMediator->WaitForRenderingSyncToFinish();
}


void Window::Add(unique_ptr<Element3d> element)
{
    scene3d.Add(std::move(element));
}

Scene &Window::Get3dScene()
{
    return scene3d;
}

void Window::NotifyOnRenderingProviderChanged(EventRenderingProviderInfo &e)
{
    for(auto subscriber : presenterSubscribers)
        subscriber->OnRenderingProviderChanged(e);
}

void Window::NotifyOnAttributesChanged(EventAttributeInfo &e)
{
    for(auto subscriber : presenterSubscribers)
        subscriber->OnAttributesChanged(e);
}

void Window::NotifyOnAttributesRemoved(EventAttributeInfo &e)
{
    for(auto subscriber : presenterSubscribers)
        subscriber->OnAttributesRemoved(e);
}

void Window::NotifyOnScaleUpdate(std::any src)
{
    for(auto subscriber : presenterSubscribers)
        subscriber->OnScaleUpdate(src);
}

void Window::NotifyOnRedraw(std::any src)
{
    for(auto subscriber : presenterSubscribers)
        subscriber->OnRedraw(src);
}

void Window::NotifyOnClose(std::any src)
{
    for(auto subscriber : presenterSubscribers)
        subscriber->OnRedraw(src);
}

void Window::NotifyOnLockCursorSizeChanged(EventResizeInfo &e)
{
    for(auto subscriber : presenterSubscribers)
        subscriber->OnLockCursorSizeChanged(e);
}

void Window::NotifyOnCursorLockStateChanged(EventCursorLockInfo &e)
{
    for(auto subscriber : presenterSubscribers)
        subscriber->OnCursorLockStateChanged(e);
}

void Window::AddPresenterSubscriber(PresenterSubscriber *subscriber)
{
    presenterSubscribers.emplace_back(subscriber);
}

void Window::RemovePresetnerSubscriber(PresenterSubscriber *subscriber)
{
    for(auto it = presenterSubscribers.begin(); it != presenterSubscribers.end(); it++)
        if(*it == subscriber)
            presenterSubscribers.erase(it);
}

std::unique_ptr<Window> Window::Create(const string &windowName)
{
    return Create(0, 0, 0, 0, windowName);
}

std::unique_ptr<Window> Window::Create(int x, int y, int width, int height, const string &windowName)
{
    return Create(x, y, width, height, windowName, WS_OVERLAPPEDWINDOW);
}

std::unique_ptr<Window> Window::Create(int x, int y, int width, int height, const string &windowName, LONG style)
{
    auto* window = new Window(x, y, width, height, windowName, style);
    window->AddOnTickSubscriber(&window->scene3d);
    window->AddRenderCommander(window->background);

    //Create all window dependencies
    auto renderingProvider = RenderingProviderManager::GetRenderingProviderManager()->Create();
    auto core = WindowsCore::Create(window, WindowsCoreArgs::Create(window->name, style));
    auto coreMediator = std::make_unique<CoreMediator>();
    core->SetRenderingProvider(std::move(renderingProvider));

    //Setup mediator dependencies
    coreMediator->SetPresenter(window);
    core->AddCoreSubscriber(coreMediator.get());
    coreMediator->SetCore(std::move(core));
    window->AddPresenterSubscriber(coreMediator.get());

    //Setup window dependencies
    window->coreMediator = std::move(coreMediator);
    window->NotifyOnRedraw(std::make_any<Window*>(window));

    return std::unique_ptr<Window>(window);
}
