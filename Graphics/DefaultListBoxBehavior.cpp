#include "DefaultListBoxBehavior.h"
#include "TableElement.h"
#include "ListBox.h"
#include "EventKeyStateInfo.h"


void DefaultListBoxBehavior::SelectClickAction(TableElement* element)
{
	UnselectElements();
	element->SetSelected(true);
	lastSelectedIndex = FindIndexByElement(element);
}

void DefaultListBoxBehavior::SelectCtrlClickAction(TableElement* element)
{
	if (element->IsSelected())
		element->SetSelected(false);
	else
	{
		element->SetSelected(true);
		lastSelectedIndex = FindIndexByElement(element);
	}
}

void DefaultListBoxBehavior::SelectShiftClickAction(TableElement* element)
{

	int shiftLastIndex = FindIndexByElement(element);
	if (shiftLastIndex < lastSelectedIndex)
	{
		int temp = lastSelectedIndex;
		lastSelectedIndex = shiftLastIndex;
		shiftLastIndex = temp;
	}


	for (int i = lastSelectedIndex; i <= shiftLastIndex; i++)
		listElements.at(i)->SetSelected(true);


}

int DefaultListBoxBehavior::FindIndexByElement(TableElement* element)
{
	for (int i = 0; i < listElements.size(); i++)
		if (listElements.at(i) == element)
			return i;
}

DefaultListBoxBehavior::DefaultListBoxBehavior(ListBox& associatedListBox) : associatedListBox(associatedListBox)
{

}

void DefaultListBoxBehavior::CreateListElement(std::wstring text, std::any value)
{
	TableElement* element = new TableElement(0, 0, 0, 0, "element"+listElements.size());
	element->SetText(text);
	element->AddKeyStateSubscriber(*this);
	element->AddMouseStateSubscriber(*this);

	listElements.push_back(element);
	associatedListBox.Add(*element);
}

std::vector<TableElement*> DefaultListBoxBehavior::GetElements()
{
	return listElements;
}

void DefaultListBoxBehavior::UnselectElements()
{
	for (TableElement* element : listElements)
		element->SetSelected(false);
}

void DefaultListBoxBehavior::OnKeyDown(EventKeyStateInfo e)
{
	inputManagerSnapshot = e.GetInputManager();
}

void DefaultListBoxBehavior::OnKeyUp(EventKeyStateInfo e)
{
	inputManagerSnapshot = e.GetInputManager();
}

void DefaultListBoxBehavior::OnKeyPressed(EventKeyStateInfo e)
{
}

void DefaultListBoxBehavior::OnMouseDown(EventMouseStateInfo e)
{
	TableElement* element = dynamic_cast<TableElement*>(e.GetSrc());
	if (element == nullptr)
		return;
	if (inputManagerSnapshot.IsKeyDown(InputManager::VirtualKeys::Control))
		SelectCtrlClickAction(element);
	else if (inputManagerSnapshot.IsKeyDown(InputManager::VirtualKeys::Shift))
		SelectShiftClickAction(element);
	else
		SelectClickAction(element);
}

void DefaultListBoxBehavior::OnMouseUp(EventMouseStateInfo e)
{

}

void DefaultListBoxBehavior::OnMousePressed(EventMouseStateInfo e)
{
}

void DefaultListBoxBehavior::OnMouseMove(EventMouseStateInfo e)
{
}

void DefaultListBoxBehavior::OnMouseEntered(EventMouseStateInfo e)
{
}

void DefaultListBoxBehavior::OnMouseLeft(EventMouseStateInfo e)
{
}
