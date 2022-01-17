#include "DefaultComboBoxBehavior.h"
#include "EventTypes/EventMoveInfo.h";
#include "EventTypes/EventResizeInfo.h"
#include "Components/ComboBox/ComboBox.h"
#include "Components/Button.h"
#include "EventTypes/EventMouseStateInfo.h"
#include "EventTypes/EventOnActivateInfo.h"
#include "Components/ComboBox/ComboElement.h"
#include "Components/ComboBox/ComboSelection.h"

DefaultComboBoxBehavior::DefaultComboBoxBehavior(ComboBox& associatedComboBox, Button* comboBoxButton, ComboSelection& selection) : associatedComboSelection(selection), associatedComboBox(associatedComboBox)
{
	this->comboBoxButton = comboBoxButton;
	associatedComboBox.AddOnResizeSubscriber(*this);
	comboBoxButton->AddMouseStateSubscriber(*this);
	comboBoxButton->AddOnActivateSubscriber(*this);
	associatedComboSelection.AddComboBoxStateSubscriber(*this);
}

void DefaultComboBoxBehavior::OnResize(EventResizeInfo e)
{
	if (comboBoxButton != nullptr)
		comboBoxButton->SetSize(e.GetSize());
}

void DefaultComboBoxBehavior::OnMouseDown(EventMouseStateInfo e)
{
}

void DefaultComboBoxBehavior::OnMouseUp(EventMouseStateInfo e)
{
	if (associatedComboBox.IsPacked() == true)
	{
		associatedComboBox.Upack();
		NotifyOnComboBoxOpened(EventComboBoxStateInfo(nullptr, associatedComboBox)); //combobox needs to be a subject
	}
	else
	{
		associatedComboBox.Pack();
		NotifyOnComboBoxClosed(EventComboBoxStateInfo(nullptr, associatedComboBox));
	}

}

void DefaultComboBoxBehavior::OnMousePressed(EventMouseStateInfo e)
{
}

void DefaultComboBoxBehavior::OnMouseMove(EventMouseStateInfo e)
{
}

void DefaultComboBoxBehavior::OnMouseEntered(EventMouseStateInfo e)
{

}

void DefaultComboBoxBehavior::OnMouseLeft(EventMouseStateInfo e)
{
}

void DefaultComboBoxBehavior::OnActiveStateChanged(EventOnActivateInfo e)
{
	if (!e.IsActive() && !associatedComboBox.IsPacked())
	{
		associatedComboBox.Pack();
		NotifyOnComboBoxClosed(EventComboBoxStateInfo(nullptr, associatedComboBox));
	}
}

void DefaultComboBoxBehavior::OnComboBoxOpened(EventComboBoxStateInfo e)
{

}

void DefaultComboBoxBehavior::OnComboBoxClosed(EventComboBoxStateInfo e)
{

}

void DefaultComboBoxBehavior::OnSelectionChanged(EventComboBoxStateInfo e)
{
	ComboElement& element = *e.GetElement();
	associatedComboBox.SetText(element.GetText());
	associatedComboBox.Pack();
	NotifyOnComboBoxClosed(EventComboBoxStateInfo(nullptr, associatedComboBox));
	NotifyOnSelectionChanged(EventComboBoxStateInfo(e.GetElement(), associatedComboBox));
}

void DefaultComboBoxBehavior::NotifyOnComboBoxOpened(EventComboBoxStateInfo e)
{
	for (ComboBoxStateSubscriber& subscriber : subscribers)
		subscriber.OnComboBoxOpened(e);
}

void DefaultComboBoxBehavior::NotifyOnComboBoxClosed(EventComboBoxStateInfo e)
{
	for (ComboBoxStateSubscriber& subscriber : subscribers)
		subscriber.OnComboBoxClosed(e);
}

void DefaultComboBoxBehavior::NotifyOnSelectionChanged(EventComboBoxStateInfo e)
{
	for (ComboBoxStateSubscriber& subscriber : subscribers)
		subscriber.OnSelectionChanged(e);
}

void DefaultComboBoxBehavior::AddComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber)
{
	subscribers.push_back(subscriber);
}

void DefaultComboBoxBehavior::RemoveComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber)
{
	for (std::vector<std::reference_wrapper<ComboBoxStateSubscriber>>::iterator it; it < subscribers.end(); it++)
		if (&it->get() == &subscriber)
			subscribers.erase(it);
}

void DefaultComboBoxBehavior::OnMouseCaptured(EventMouseStateInfo e)
{

}
