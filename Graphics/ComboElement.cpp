#include "ComboElement.h"
#include "EventMouseStateInfo.h"
#include "Button.h"
#include "ComboSelection.h"
#include <Windows.h>
#include <gdiplus.h>

ComboElement::ComboElement(ComboSelection& comboSelection, std::wstring displayText) : comboSelection(comboSelection), text(displayText)
{
	elementGui == nullptr;
}


std::wstring ComboElement::GetText()
{
	return text;
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
		elementGui->SetProperty("background-color", Gdiplus::Color(200, 200, 200));

	elementGui->SetText(text);
	elementGui->AddMouseStateSubscriber(*this);
	comboSelection.AddComboElementGui(*elementGui);
}

void ComboElement::RemoveElementGui()
{
	delete elementGui;
	elementGui = nullptr;
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

void ComboElement::NotifyOnMouseMove(EventMouseStateInfo e)
{
	if (elementGui != nullptr)
		elementGui->NotifyOnMouseMove(e);
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
	mouseSubscribers.push_back(subscriber);
}

void ComboElement::RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	for (std::vector<reference_wrapper<MouseStateSubscriber>>::iterator it = mouseSubscribers.begin(); it != mouseSubscribers.end(); it++)
		if (&it->get() == &subscriber)
			mouseSubscribers.erase(it);
}

bool ComboElement::HasMouseEntered()
{
	if (elementGui == nullptr)
		return false;
	
	return elementGui->HasMouseEntered();
}

void ComboElement::OnMouseDown(EventMouseStateInfo e)
{
	for (MouseStateSubscriber& subscriber : mouseSubscribers)
		subscriber.OnMouseDown(e);
}

void ComboElement::OnMouseUp(EventMouseStateInfo e)
{
	for (MouseStateSubscriber& subscriber : mouseSubscribers)
		subscriber.OnMouseUp(e);
	Button* button = dynamic_cast<Button*>(e.GetSrc());
	comboSelection.UnselectOptions();
	isSelected = true;
	button->SetProperty("background-color", Gdiplus::Color(150, 150, 150));
}

void ComboElement::OnMousePressed(EventMouseStateInfo e)
{
	
	for (MouseStateSubscriber& subscriber : mouseSubscribers)
		subscriber.OnMousePressed(EventMouseStateInfo(e) );
}

void ComboElement::OnMouseMove(EventMouseStateInfo e)
{
	for (MouseStateSubscriber& subscriber : mouseSubscribers)
		subscriber.OnMouseMove(e);
}

void ComboElement::OnMouseEntered(EventMouseStateInfo e)
{
	for (MouseStateSubscriber& subscriber : mouseSubscribers)
		subscriber.OnMouseEntered(e);
}

void ComboElement::OnMouseLeft(EventMouseStateInfo e)
{
	for (MouseStateSubscriber& subscriber : mouseSubscribers)
		subscriber.OnMouseLeft(e);
}
