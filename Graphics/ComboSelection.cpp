#include "ComboSelection.h"
#include "ComboElement.h"
#include "WindowFrame.h"
#include "Grid.h"
#include "Component.h"



void ComboSelection::CreateGui(int x, int y, int width, int height)
{
	int totalHeight = elementHeight * comboElements.size();
	comboSelectionFrame = new WindowFrame(x, y, width, totalHeight, "ComboSelection");
	comboSelectionFrame->RemoveWindowStyle(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
	comboSelectionFrame->AddWindowExtendedStyle(WS_EX_TOOLWINDOW);
	comboSelectionFrame->SetSize(width, totalHeight);

	comboGrid = new Grid(0, 0, width, totalHeight);
	comboGrid->SetGridColumns({ width });
	comboGrid->SetDefaultRowSize(elementHeight);
	comboSelectionFrame->Add(*comboGrid);

	//Iterate through all the comboElements and spawn their gui
	for (ComboElement* element : comboElements)
		element->DisplayElementGui();
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

void ComboSelection::OnMouseDown(EventMouseStateInfo e)
{

}

void ComboSelection::OnMouseUp(EventMouseStateInfo e)
{
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


ComboSelection::ComboSelection()
{
	comboGrid = nullptr;
	comboSelectionFrame = nullptr;
}

void ComboSelection::AddComboElementGui(Button& button)
{
	comboGrid->Add((Component&)button);
}

MouseStateSubject& ComboSelection::CreateComboElement(std::wstring comboElementText)
{
	ComboElement* element = new ComboElement(*this, comboElementText);
	element->AddMouseStateSubscriber(*this);
	comboElements.push_back(element);
	return *element;
}
