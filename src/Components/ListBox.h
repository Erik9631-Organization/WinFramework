#pragma once
#include "Panel.h"
#include "Components/Grid/Grid.h"
#include "ScrollBar.h"
#include "Behavior/DefaultListBoxBehavior.h"
#include <any>
#include "api/Draggable.h"
#include "DragManager.h"

class ListBox : public Panel, public Draggable, public DragSubject, public DropSubject
{
private:
	Grid* layout;
	ScrollBar* trackbar;
	DragManager dragManager;
	DefaultListBoxBehavior behavior;


public:
	ListBox();
	/**
	 * \param name the identification name of the component. This value is not a display value.
	 */
	ListBox(std::string name);

	/**
	 * \param x the X position of the grid.
	 * \param y the Y position of the grid
	 * \param width the width of the grid
	 * \param height the height of the grid.
	 * \param name the identification name of the grid. This is not a display value.
	 */
	ListBox(int x, int y, int width, int height, std::string name);

	/**
	 * \return returns a list of listbox elements.
	 */
	std::vector<TableElement*>GetElements();

	/**
	 * Creates a list box element with the specified name and value
	 * \param name the display value of the element
	 * \param value the value the element contains.
	*/
	void CreateListElement(std::wstring name, std::any value);

	void Add(unique_ptr<UiElement> component) override;

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
