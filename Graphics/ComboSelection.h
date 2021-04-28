#pragma once
#include <vector>
#include <string>
#include "MouseStateSubject.h"
#include "MouseStateSubscriber.h"
#include "ComboBoxStateSubject.h"
#include <any>

class Button;
class ComboElement;
class WindowFrame;
class Grid;

class ComboSelection : public MouseStateSubscriber, public ComboBoxStateSubject
{
private:
	std::vector<std::reference_wrapper<ComboBoxStateSubscriber>> comboBoxStateSubscribers;
	std::vector<ComboElement*>comboElements;
	WindowFrame* comboSelectionFrame;
	Grid* comboGrid;
	int elementHeight = 30;
	int selectedIndex = 0;
	static int numberOfBoxes;

public:
	ComboSelection();
	void AddComboElementGui(Button& button);
	MouseStateSubject& CreateComboElement(std::wstring comboElementText, std::any value);
	void CreateGui(int x, int y, int width, int height);
	void CloseGui();
	void SetElementHeight(int width);
	void UnselectOptions();
	ComboElement& GetSelectedElement();
	std::vector<ComboElement*> GetElements();

	 // Inherited via MouseStateSubscriber
	 virtual void OnMouseDown(EventMouseStateInfo e) override;
	 virtual void OnMouseUp(EventMouseStateInfo e) override;
	 virtual void OnMousePressed(EventMouseStateInfo e) override;
	 virtual void OnMouseMove(EventMouseStateInfo e) override;
	 virtual void OnMouseEntered(EventMouseStateInfo e) override;
	 virtual void OnMouseLeft(EventMouseStateInfo e) override;

	 // Inherited via ComboboxStateSubject
	 virtual void NotifyOnComboBoxOpened(EventComboBoxStateInfo e);
	 virtual void NotifyOnComboBoxClosed(EventComboBoxStateInfo e);
	 virtual void NotifyOnSelectionChanged(EventComboBoxStateInfo e);

	 virtual void AddComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber);
	 virtual void RemoveComboBoxStateSubscriber(ComboBoxStateSubscriber& subscriber);


};

