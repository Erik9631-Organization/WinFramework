#pragma once
#include <string>
#include <any>
#include <vector>
#include "KeyStateSubscriber.h"
#include "MouseStateSubscriber.h"
#include "InputManager.h"

class ListBox;
class TableElement;


class DefaultListBoxBehavior : public KeyStateSubscriber, public MouseStateSubscriber
{
private:
	ListBox& associatedListBox;
	std::vector<TableElement*> listElements;
	InputManager inputManagerSnapshot;
	void SelectClickAction(TableElement* element);
	void SelectCtrlClickAction(TableElement* element);
	void SelectShiftClickAction(TableElement* element);
	int lastSelectedIndex = -1;

	int FindIndexByElement(TableElement* element);
public:
	DefaultListBoxBehavior(ListBox& associatedListBox);
	void CreateListElement(std::wstring name, std::any value);
	std::vector<TableElement*> GetElements();
	void UnselectElements();

	// Inherited via KeyStateSubscriber
	virtual void OnKeyDown(EventKeyStateInfo e) override;
	virtual void OnKeyUp(EventKeyStateInfo e) override;
	virtual void OnKeyPressed(EventKeyStateInfo e) override;

	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;
	virtual void OnMouseUp(EventMouseStateInfo e) override;
	virtual void OnMousePressed(EventMouseStateInfo e) override;
	virtual void OnMouseMove(EventMouseStateInfo e) override;
	virtual void OnMouseEntered(EventMouseStateInfo e) override;
	virtual void OnMouseLeft(EventMouseStateInfo e) override;
};

