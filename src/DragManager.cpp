#include "DragManager.h"
#include "api/Draggable.h"
#include "EventTypes/EventMouseStateInfo.h"
#include "Events/MouseStateSubject.h"
#include "Events/DragSubscriber.h"
#include "Events/DropSubscriber.h"
#include "Core/Windows/WindowsCore.h"

bool DragManager::isDragging = false;
Draggable* DragManager::currentDragObj = nullptr;
DragManager* DragManager::srcManager = nullptr;


void DragManager::OnDragStart()
{
	WindowsCore::ConsoleWrite("Drag started!");
	isDragging = true;
	currentDragObj = associatedDraggable;
	srcManager = this;
	NotifyOnDragStart(EventOnDragInfo(*currentDragObj));
}

void DragManager::OnDragEnd()
{
	WindowsCore::ConsoleWrite("Drag ended!");
	if (currentDragObj == associatedDraggable) // Cant drop on itself
	{
		// Reset states
		srcManager = nullptr;
		currentDragObj = nullptr;
		isDragging = false;
		return;
	}

	srcManager->NotifyOnDragEnd(EventOnDragInfo(*currentDragObj)); // Notify the original that the drag has ended
	NotifyOnDrop(EventOnDragInfo(*currentDragObj)); // Then notify the current that drop happened

	//Reset states
	srcManager = nullptr; 
	currentDragObj = nullptr;
	isDragging = false;
}

DragManager::DragManager(MouseStateSubject& subject) : DragManager(subject, nullptr)
{

}

DragManager::DragManager(MouseStateSubject& subject, Draggable* associatedDraggable)
{
	this->associatedDraggable = associatedDraggable;
	subject.AddMouseStateSubscriber(*this);
}

void DragManager::SetAssociatedDraggable(Draggable* associatedDraggable)
{
	this->associatedDraggable = associatedDraggable;
}

void DragManager::OnMouseDown(EventMouseStateInfo e)
{
	mouseDown = true;
}

void DragManager::OnMouseUp(EventMouseStateInfo e)
{
	if (isDragging == true)
		OnDragEnd();
	mouseDown = false;
}

void DragManager::OnMousePressed(EventMouseStateInfo e)
{
}

void DragManager::OnMouseMove(EventMouseStateInfo e)
{
	if (mouseDown == true && isDragging == false)
		OnDragStart();

}

void DragManager::OnMouseEntered(EventMouseStateInfo e)
{
}

void DragManager::OnMouseLeft(EventMouseStateInfo e)
{
	mouseDown = false;
}

void DragManager::NotifyOnDrop(EventOnDragInfo e)
{
	for (DropSubscriber& subscriber : dropSubscribers)
		subscriber.OnDrop(e);
}

void DragManager::NotifyOnDragStart(EventOnDragInfo e)
{
	for (DragSubscriber& subscriber : dragSubscribers)
		subscriber.OnDragStart(e);
}

void DragManager::NotifyOnDragEnd(EventOnDragInfo e)
{
	for (DragSubscriber& subscriber : dragSubscribers)
		subscriber.OnDragEnd(e);
}

void DragManager::AddOnDragSubscriber(DragSubscriber& subscriber)
{
	dragSubscribers.push_back(subscriber);
}

void DragManager::RemoveOnDragSubscriber(DragSubscriber& subscriber)
{
	for (std::vector<std::reference_wrapper<DragSubscriber>>::iterator it = dragSubscribers.begin(); it != dragSubscribers.end(); it++)
	{
		if (&it->get() == &subscriber)
		{
			dragSubscribers.erase(it);
			return;
		}

	}
}

void DragManager::AddOnDropSubscriber(DropSubscriber& subscriber)
{
	dropSubscribers.push_back(subscriber);
}

void DragManager::RemoveOnDropSubscriber(DropSubscriber& subscriber)
{
	for (std::vector<std::reference_wrapper<DropSubscriber>>::iterator it = dropSubscribers.begin(); it != dropSubscribers.end(); it++)
	{
		if (&it->get() == &subscriber)
		{
			dropSubscribers.erase(it);
			return;
		}

	}
}

void DragManager::OnMouseCaptured(EventMouseStateInfo e)
{

}
