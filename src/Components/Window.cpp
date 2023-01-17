#include "Window.h"
#include "Core/Windows/WindowsCore.h"
#include <thread>
#include <mutex>
#include "ApplicationController.h"
#include <string>
#include "EventMouseStateInfo.h"
#include "EventKeyStateInfo.h"
#include "CoreArgs.h"
#include "RenderingProviderManager.h"
#include "CoreManager.h"
#include <iostream>
#include "DefaultRenderCommandHandler.h"

using namespace std;

void Window::SetSize(float width, float height, bool emit)
{
    UiElement::SetSize(width, height, emit);
    if(emit)
        NotifyOnScaleUpdate(std::make_any<Presenter*>(this));
}

void Window::SetSize(glm::vec4 size, bool emit)
{
    SetSize(size.x, size.y, emit);
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

void Window::SetPosition(float x, float y, float z, float w, bool emit)
{
    UiElement::SetPosition(x, y, 0, 0, emit);
    if(emit)
        NotifyOnScaleUpdate(std::make_any<Presenter*>(this));
}

void Window::SetPosition(glm::vec4 position, bool emit)
{
    SetPosition(position.x, position.y, 0, 0, emit);
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

Window::Window(int x, int y, int width, int height, string windowName) : UiElement(x, y, width, height, windowName)
{
	componentType = "Window";
	background.SetColor({255, 255, 255});
}

UiElement & Window::Add(unique_ptr<UiElement> component)
{
    auto& element = *component;
	UiElement::Add(std::move(component));
    return element;
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
        subscriber->Redraw(src);
}

void Window::NotifyOnClose(std::any src)
{
    for(auto subscriber : presenterSubscribers)
        subscriber->OnClose(src);
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
    auto* window = new Window(x, y, width, height, windowName);
    window->AddOnTickSubscriber(&window->scene3d);
    //window->AddRenderCommander(window->background);

    //CreateElement all window DEPENDENCIES
    //TODO use try and catch here
    auto renderer = new DefaultRenderCommandHandler();
    auto renderingProvider = std::unique_ptr<AsyncRenderCommandHandler>(renderer);
    if(renderingProvider == nullptr)
    {
        cout << "Error, failed to create window" << endl;
        return nullptr;
    }

    auto core = CoreManager::GetCoreManager()->Create(CoreArgs::Create(window->name, 0, window));
    core->SetRenderer(std::move(renderingProvider));

    //CreateElement core mediator
    auto coreMediator = std::make_unique<CoreMediator>(window, std::move(core));

    //Setup window dependencies
    window->coreMediator = std::move(coreMediator);

    //Handle graphics
    renderer->RequestRectangleProxy([window](std::unique_ptr<RectangleProxy> rectangleProxy){
        window->backgroundProxy = std::move(rectangleProxy);
        window->backgroundProxy->SetSize({window->GetWidth(), window->GetWidth(), 0, 0});
        window->backgroundProxy->SetPosition({0, 0, 0, 1});
        window->backgroundProxy->SetColor({255, 255, 255, 255});
        window->backgroundProxy->SetFill(true);
    });

    renderer->RequestRectangleProxy([window](std::unique_ptr<RectangleProxy> rectangleProxy){
        window->backgroundProxy = std::move(rectangleProxy);
        window->backgroundProxy->SetSize({100, 100, 0, 0});
        window->backgroundProxy->SetPosition({50, 100, 0, 1});
        window->backgroundProxy->SetColor({100, 100, 100, 255});
        window->backgroundProxy->SetFill(true);
        glm::vec4 halfSize;
        halfSize.x = window->backgroundProxy->GetSize().x / 2.0f;
        halfSize.y = window->backgroundProxy->GetSize().y;

        window->backgroundProxy->SetViewPort(glm::vec4{50, 100, 0, 0}, halfSize);
        window->coreMediator->Redraw(std::make_any<Presenter *>(window));
    });
    return std::unique_ptr<Window>(window);
}

AsyncRenderCommandHandler *Window::GetRenderer()
{
    return coreMediator->GetRenderer();
}
