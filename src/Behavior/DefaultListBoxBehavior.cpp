#include "DefaultListBoxBehavior.h"
#include "TableElement.h"
#include "ListBox.h"
#include "EventKeyStateInfo.h"
using namespace std;

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
	associatedListBox.AddOnDropSubscriber(*this);
}

void DefaultListBoxBehavior::CreateListElement(std::wstring text, std::any value)
{
	auto element = std::make_unique<TableElement>(0, 0, 0, 0, "element"+ to_string(listElements.size()));
	element->SetText(text);
	element->AddKeyStateSubscriber(*this);
	element->AddMouseStateSubscriber(*this);

	listElements.push_back(element.get());
	associatedListBox.Add(std::move(element));
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
	lastInputSnapshot = e.GetInputManager();
}

void DefaultListBoxBehavior::OnKeyUp(EventKeyStateInfo e)
{
	lastInputSnapshot = e.GetInputManager();
}

void DefaultListBoxBehavior::OnKeyPressed(EventKeyStateInfo e)
{
}

void DefaultListBoxBehavior::OnMouseDown(EventMouseStateInfo e)
{
	e.SetRecursive(false);
	associatedListBox.NotifyOnMouseDown(e);
}

void DefaultListBoxBehavior::OnMouseUp(EventMouseStateInfo e)
{
	TableElement* element = dynamic_cast<TableElement*>(e.GetSource());
	if (element == nullptr)
		return;
	if (lastInputSnapshot.IsKeyDown(InputManager::VirtualKeys::Control))
		SelectCtrlClickAction(element);
	else if (lastInputSnapshot.IsKeyDown(InputManager::VirtualKeys::Shift))
		SelectShiftClickAction(element);
	else
		SelectClickAction(element);
	e.SetRecursive(false);
	associatedListBox.NotifyOnMouseUp(e);
}

void DefaultListBoxBehavior::OnMousePressed(EventMouseStateInfo e)
{
	e.SetRecursive(false);
	associatedListBox.NotifyOnMousePressed(e);
}

void DefaultListBoxBehavior::OnMouseMove(EventMouseStateInfo e)
{
	e.SetRecursive(false);
	associatedListBox.NotifyOnMouseHover(e);
}

void DefaultListBoxBehavior::OnMouseEntered(EventMouseStateInfo e)
{

}

void DefaultListBoxBehavior::OnMouseLeft(EventMouseStateInfo e)
{
	e.SetRecursive(false);
	associatedListBox.NotifyOnMouseLeave(e);
}

std::any DefaultListBoxBehavior::GetDragContent()
{
	draggedElements.clear();
	for (TableElement* element : listElements)
		if (element->IsSelected())
			draggedElements.push_back(element);

	return std::make_any<std::vector<TableElement*>*>(&draggedElements);
}

void DefaultListBoxBehavior::OnDragOver(EventOnDragInfo e)
{

}

void DefaultListBoxBehavior::OnDrop(EventOnDragInfo e)
{
    auto draggable = dynamic_cast<Draggable*>(e.GetSource());
	std::vector<TableElement*>* dragContent = std::any_cast<std::vector<TableElement*>*>(draggable->GetDragContent());
	if (dragContent == nullptr)
		return;
	for (TableElement* element : *dragContent)
		CreateListElement(element->GetText(), element->GetValue());
}

void DefaultListBoxBehavior::OnMouseCaptured(EventMouseStateInfo e)
{

}
