#include "DefaultComboBoxBehavior.h"
#include "EventMoveInfo.h";
#include "EventResizeInfo.h"
#include "ComboBox.h"
#include "Button.h"
#include "EventMouseStateInfo.h"
#include "EventOnActivateInfo.h"
#include "ComboElement.h"
#include "ComboSelection.h"

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
	associatedComboBox.Upack();
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
	if (!e.IsActive())
		associatedComboBox.Pack();
}

void DefaultComboBoxBehavior::OnComboBoxOpened(EventComboBoxStateInfo e)
{

}

void DefaultComboBoxBehavior::OnComboBoxClosed(EventComboBoxStateInfo e)
{

}

void DefaultComboBoxBehavior::OnSelectionChanged(EventComboBoxStateInfo e)
{
	ComboElement& element = e.GetElement();
	associatedComboBox.SetText(e.GetElement().GetText());
	associatedComboBox.Pack();
}
