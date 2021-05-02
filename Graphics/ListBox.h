#pragma once
#include "Panel.h"
#include "Grid.h"
#include "TrackBar.h"
#include "DefaultListBoxBehavior.h"
#include <any>
#include "Draggable.h"
#include "DragManager.h"

class ListBox : public Panel, public Draggable, public DragSubject, public DropSubject
{
private:
	Grid layout;
	TrackBar trackbar;
	DragManager dragManager;
	DefaultListBoxBehavior behavior;


public:
	ListBox();
	ListBox(std::string name);
	ListBox(int x, int y, int width, int height, std::string name);
	std::vector<TableElement*>GetElements();
	void CreateListElement(std::wstring name, std::any value);
	void Add(Component& component) override;

	// Inherited via Draggable
	virtual std::any GetDragContent() override;

	// Inherited via DragSubject
	virtual void NotifyOnDragStart(EventOnDragInfo e) override;
	virtual void NotifyOnDragEnd(EventOnDragInfo e) override;
	virtual void AddOnDragSubscriber(DragSubscriber& subscriber) override;
	virtual void RemoveOnDragSubscriber(DragSubscriber& subscriber) override;

	// Inherited via DropSubject
	virtual void NotifyOnDrop(EventOnDragInfo e) override;
	virtual void AddOnDropSubscriber(DropSubscriber& subscriber) override;
	virtual void RemoveOnDropSubscriber(DropSubscriber& subscriber) override;
};
