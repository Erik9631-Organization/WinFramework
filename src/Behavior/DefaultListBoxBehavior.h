#pragma once
#include <string>
#include <any>
#include <vector>
#include "Events/KeyStateSubscriber.h"
#include "Events/MouseStateSubscriber.h"
#include "Utils/InputManager.h"
#include "Components/Draggable.h"
#include "Events/DragSubscriber.h"
#include "Events/DropSubscriber.h"

class ListBox;
class TableElement;


class DefaultListBoxBehavior : public KeyStateSubscriber, public MouseStateSubscriber, public Draggable, public DropSubscriber
{
private:
	ListBox& associatedListBox;
	std::vector<TableElement*> listElements;
	std::vector<TableElement*> draggedElements;
	InputManager lastInputSnapshot;
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

	// Inherited via Draggable
	virtual std::any GetDragContent() override;

	// Inherited via DropSubscriber
	virtual void OnDragOver(EventOnDragInfo e) override;
	virtual void OnDrop(EventOnDragInfo e) override;

    void OnMouseCaptured(EventMouseStateInfo e) override;
};

