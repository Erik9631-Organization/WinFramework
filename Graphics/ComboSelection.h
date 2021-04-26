#pragma once
#include <vector>
#include <string>
#include "MouseStateSubject.h"
#include "MouseStateSubscriber.h"

class Button;
class ComboElement;
class WindowFrame;
class Grid;

class ComboSelection : public MouseStateSubscriber
{
private:
	std::vector<ComboElement*>comboElements;
	WindowFrame* comboSelectionFrame;
	Grid* comboGrid;
	int elementHeight = 30;
	int selectedIndex = 0;

public:
	ComboSelection();
	void AddComboElementGui(Button& button);
	MouseStateSubject& CreateComboElement(std::wstring comboElementText);
	void CreateGui(int x, int y, int width, int height);
	void SetElementHeight(int width);

	void UnselectOptions();

	 // Inherited via MouseStateSubscriber
	 virtual void OnMouseDown(EventMouseStateInfo e) override;
	 virtual void OnMouseUp(EventMouseStateInfo e) override;
	 virtual void OnMousePressed(EventMouseStateInfo e) override;
	 virtual void OnMouseMove(EventMouseStateInfo e) override;
	 virtual void OnMouseEntered(EventMouseStateInfo e) override;
	 virtual void OnMouseLeft(EventMouseStateInfo e) override;
};

