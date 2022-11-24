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
using namespace std;

void Window::SetSize(float width, float height, bool emit)
{
    UiElement::SetSize(width, height, emit);
    if(emit)
        NotifyOnScaleUpdate(std::make_any<Presenter*>(this));
}

void Window::SetSize(glm::vec2 size, bool emit)
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

void Window::SetPosition(float x, float y, bool emit)
{
    UiElement::SetPosition(x, y, emit);
    if(emit)
        NotifyOnScaleUpdate(std::make_any<Presenter*>(this));
}

void Window::SetPosition(glm::vec2 point, bool emit)
{
    SetPosition(point.x, point.y, emit);
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
