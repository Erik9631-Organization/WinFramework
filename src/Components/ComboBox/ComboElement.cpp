#include "ComboElement.h"
#include "EventTypes/EventMouseStateInfo.h"
#include "Components/Button.h"
#include "ComboSelection.h"
#include <Windows.h>
#include <gdiplus.h>
#include <mutex>
#include "Core/Windows/WindowsCore.h"

ComboElement::ComboElement(ComboSelection& comboSelection, std::wstring displayText, std::any value) : comboSelection(comboSelection), text(displayText)
{
	this->value = value;
	elementGui = nullptr;
	deleteSyncMutex = new std::mutex();
	deleteSync = new std::condition_variable();
}


std::wstring ComboElement::GetText()
{
	return text;
}

std::any ComboElement::GetValue()
{
	return value;
}

void ComboElement::SetText(std::wstring text)
{
	this->text = text;
}

void ComboElement::DisplayElementGui()
{
	if (elementGui != nullptr)
		return;

	elementGui = new Button(0, 0, 0, 0);

	if(isSelected == true)
		elementGui->SetProperty<Vector3>("background-color", {75, 75, 75});

	elementGui->SetText(text);
	elementGui->AddMouseStateSubscriber(*this);
	comboSelection.AddComboElementGui(std::unique_ptr<Button>(elementGui));
}

void ComboElement::RemoveElementGui()
{
	std::unique_lock<std::mutex> lock(*deleteSyncMutex);

	std::thread::id deleteThreadId = std::this_thread::get_id();
	deleteSync->wait(lock, [=] {return eventSentSignalContinue || (eventThreadId == deleteThreadId); }); // false means wait;
	elementGui = nullptr;
	delete elementGui;
}

bool ComboElement::IsSelected()
{
	return isSelected;
}

void ComboElement::SetSelected(bool selected)
{
	isSelected = selected;
}

void ComboElement::NotifyOnMouseDown(EventMouseStateInfo e)
{
	if (elementGui != nullptr)
		elementGui->NotifyOnMouseDown(e);
}

void ComboElement::NotifyOnMouseUp(EventMouseStateInfo e)
{
	if (elementGui != nullptr)
		elementGui->NotifyOnMouseUp(e);
}

void ComboElement::NotifyOnMousePressed(EventMouseStateInfo e)
{
	if (elementGui != nullptr)
		elementGui->NotifyOnMousePressed(e);
}

void ComboElement::NotifyOnMouseHover(EventMouseStateInfo e)
{
	if (elementGui != nullptr)
		elementGui->NotifyOnMouseHover(e);
}

void ComboElement::NotifyOnMouseEnter(EventMouseStateInfo e)
{
	if (elementGui != nullptr)
		elementGui->NotifyOnMouseEnter(e);
}

void ComboElement::NotifyOnMouseLeave(EventMouseStateInfo e)
{
	if (elementGui != nullptr)
		elementGui->NotifyOnMouseLeave(e);
}

void ComboElement::AddMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	comboBoxStateSubscribers.push_back(subscriber);
}

void ComboElement::RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	for (std::vector<reference_wrapper<MouseStateSubscriber>>::iterator it = comboBoxStateSubscribers.begin(); it != comboBoxStateSubscribers.end(); it++)
		if (&it->get() == &subscriber)
			comboBoxStateSubscribers.erase(it);
}

bool ComboElement::HasMouseEntered()
{
	if (elementGui == nullptr)
		return false;
	
	return elementGui->HasMouseEntered();
}

void ComboElement::OnMouseDown(EventMouseStateInfo e)
{
	for (MouseStateSubscriber& subscriber : comboBoxStateSubscribers)
		subscriber.OnMouseDown(EventMouseStateInfo(e, e.GetMousePosition(), this));
}

void ComboElement::OnMouseUp(EventMouseStateInfo e)
{
	eventSentSignalContinue = false;
	eventThreadId = std::this_thread::get_id();

	Button* button = dynamic_cast<Button*>(e.GetSrc());
	comboSelection.UnselectOptions();
	isSelected = true;
	button->SetProperty<Vector3>("background-color", {150, 150, 150});
	for (MouseStateSubscriber& subscriber : comboBoxStateSubscribers)
	{
		if (elementGui != nullptr)
			subscriber.OnMouseUp(EventMouseStateInfo(e, e.GetMousePosition(), this));
	}

	eventSentSignalContinue = true;
	deleteSync->notify_all();
}

void ComboElement::OnMousePressed(EventMouseStateInfo e)
{
	
	for (MouseStateSubscriber& subscriber : comboBoxStateSubscribers)
		subscriber.OnMousePressed(EventMouseStateInfo(EventMouseStateInfo(e, e.GetMousePosition(), this)) );
}

void ComboElement::OnMouseMove(EventMouseStateInfo e)
{
	for (MouseStateSubscriber& subscriber : comboBoxStateSubscribers)
		subscriber.OnMouseMove(EventMouseStateInfo(e, e.GetMousePosition(), this));
}

void ComboElement::OnMouseEntered(EventMouseStateInfo e)
{
	for (MouseStateSubscriber& subscriber : comboBoxStateSubscribers)
		subscriber.OnMouseEntered(EventMouseStateInfo(e, e.GetMousePosition(), this));
}

void ComboElement::OnMouseLeft(EventMouseStateInfo e)
{
	for (MouseStateSubscriber& subscriber : comboBoxStateSubscribers)
		subscriber.OnMouseLeft(EventMouseStateInfo(e, e.GetMousePosition(), this));
}

void ComboElement::NotifyOnMouseCapture(EventMouseStateInfo e)
{
    elementGui->NotifyOnMouseCapture(e);
}

bool ComboElement::IsMouseCaptured()
{
    return elementGui->IsMouseCaptured();
}

void ComboElement::OnMouseCaptured(EventMouseStateInfo e)
{

}

void ComboElement::SetMouseCaptured(bool state)
{

}
