#pragma once
#include "MouseStateSubscriber.h"
#include "DragSubscriber.h"
#include "DragSubscriber.h"
#include "DragSubject.h"
#include "DropSubject.h"
#include <vector>

#include <any>
class Draggable;
class MouseStateSubject;

class DragManager : public MouseStateSubscriber, public DragSubject, public DropSubject
{
private:
	static Draggable* currentDragObj;
	static bool isDragging;
	static DragManager* srcManager;

	Draggable* associatedDraggable;
	std::vector<std::reference_wrapper<DragSubscriber>> dragSubscribers;
	std::vector<std::reference_wrapper<DropSubscriber>> dropSubscribers;
	bool mouseDown = false;
	void OnDragStart();
	void OnDragEnd();
public:
	DragManager(MouseStateSubject& subject);
	DragManager(MouseStateSubject& subject, Draggable* associatedDraggable);

	void SetAssociatedDraggable(Draggable* associatedDraggable);
	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;

	virtual void OnMouseUp(EventMouseStateInfo e) override;

	virtual void OnMousePressed(EventMouseStateInfo e) override;

	virtual void OnMouseMove(EventMouseStateInfo e) override;

	virtual void OnMouseEntered(EventMouseStateInfo e) override;

	virtual void OnMouseLeft(EventMouseStateInfo e) override;


	// Inherited via DropSubject
	virtual void NotifyOnDrop(EventOnDragInfo e) override;


	// Inherited via DragSubject
	virtual void NotifyOnDragStart(EventOnDragInfo e) override;

	virtual void NotifyOnDragEnd(EventOnDragInfo e) override;


	// Inherited via DragSubject
	virtual void AddOnDragSubscriber(DragSubscriber& subscriber) override;

	virtual void RemoveOnDragSubscriber(DragSubscriber& subscriber) override;


	// Inherited via DropSubject
	virtual void AddOnDropSubscriber(DropSubscriber& subscriber) override;

	virtual void RemoveOnDropSubscriber(DropSubscriber& subscriber) override;

};

