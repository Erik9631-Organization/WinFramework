#include "ComboSelection.h"
#include "ComboElement.h"
#include "Components/Window.h"
#include "Components/Grid/Grid.h"
#include "Components/UiElement.h"
#include "Components/CoreWindow.h"
#include "Events/ComboBoxStateSubscriber.h"

int ComboSelection::numberOfBoxes = 0;

void ComboSelection::CreateGui(int x, int y, int width, int height)
{
	if (comboSelectionFrame != nullptr)
		return;

	int totalHeight = elementHeight * comboElements.size();
	comboSelectionFrame = new Window(x, y, width, totalHeight, "ComboSelection" + to_string(numberOfBoxes), WS_VISIBLE | WS_POPUP);

	comboSelectionFrame->AddWindowExtendedStyle(WS_EX_TOOLWINDOW);
	comboSelectionFrame->SetSize(width, totalHeight);

	comboGrid = new Grid(0, 0, width, totalHeight);
	comboGrid->SetGridColumns({ width });
	comboGrid->SetDefaultRowSize(elementHeight);
	comboSelectionFrame->Add(std::unique_ptr<Grid>(comboGrid));

	//Iterate through all the comboElements and spawn their gui
	for (ComboElement* element : comboElements)
		element->DisplayElementGui();
	numberOfBoxes++;
}

void ComboSelection::CloseGui()
{
	if (comboSelectionFrame == nullptr)
		return;

	for (ComboElement* element : comboElements) // First clear elements, then close window
		element->RemoveElementGui();

	comboSelectionFrame->CloseWindow();
	numberOfBoxes--;

	comboSelectionFrame = nullptr;
}

void ComboSelection::SetElementHeight(int width)
{
	elementHeight = width;
}

void ComboSelection::UnselectOptions()
{
	for (ComboElement* element : comboElements)
		element->SetSelected(false);
}

std::vector<ComboElement*>  ComboSelection::GetElements()
{
	return comboElements;
}

void ComboSelection::OnMouseDown(EventMouseStateInfo e)
{

}

ComboElement& ComboSelection::GetSelectedElement()
{
	return *comboElements.at(selectedIndex);
}

void ComboSelection::OnMouseUp(EventMouseStateInfo e)
{
	ComboElement* element = dynamic_cast<ComboElement*>(e.GetSrc());
	EventComboBoxStateInfo info = EventComboBoxStateInfo(element, *this);
	for (int i = 0; i < comboElements.size(); i++)
		if (comboElements.at(i) == e.GetSrc())
			selectedIndex = i;


	NotifyOnSelectionChanged(info);
}

void ComboSelection::OnMousePressed(EventMouseStateInfo e)
{
}

void ComboSelection::OnMouseMove(EventMouseStateInfo e)
{
}

void ComboSelection::OnMouseEntered(EventMouseStateInfo e)
{
}

void ComboSelection::OnMouseLeft(EventMouseStateInfo e)
{
}

void ComboSelection::NotifyOnComboBoxOpened(EventComboBoxStateInfo e)
{
}

void ComboSelection::NotifyOnComboBoxClosed(EventComboBoxStateInfo e)
{
}

void ComboSelection::NotifyOnSelectionChanged(EventComboBoxStateInfo e)
{
	for (ComboBoxStateSubscriber& subscriber : comboBoxStateSubscribers)
		subscriber.OnSelectionChanged(e);
}

void ComboSelection::AddComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber)
{
	comboBoxStateSubscribers.push_back(subscriber);
}

void ComboSelection::RemoveComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber)
{
	for (std::vector<reference_wrapper<ComboBoxStateSubscriber>>::iterator it = comboBoxStateSubscribers.begin(); it != comboBoxStateSubscribers.end(); it++)
		if (&it->get() == &subscriber)
			comboBoxStateSubscribers.erase(it);
}


ComboSelection::ComboSelection()
{
	comboGrid = nullptr;
	comboSelectionFrame = nullptr;
}

void ComboSelection::AddComboElementGui(unique_ptr<UiElement> element)
{
	comboGrid->Add(std::move(element));
}

MouseStateSubject& ComboSelection::CreateComboElement(std::wstring comboElementText, std::any value)
{
	ComboElement* element = new ComboElement(*this, comboElementText, value);
	element->AddMouseStateSubscriber(*this);
	comboElements.push_back(element);
	return *element;
}

void ComboSelection::OnMouseCaptured(EventMouseStateInfo e)
{

}
