#include "ListBox.h"
#include <string>

ListBox::ListBox() : ListBox("")
{

}

ListBox::ListBox(std::string name) : ListBox(0, 0, 0, 0, name)
{

}

ListBox::ListBox(int x, int y, int width, int height, std::string name) : Panel(x, y, width, height, name), layout(0, 0, width, height+50), dragManager(*this, this), behavior(*this)
{
	this->Panel::Add(trackbar);
	trackbar.SetWidth(10);
	trackbar.Control(this);
	this->Panel::Add(layout);
	layout.SetAutoExtend(true);
	layout.SetGridColumns({ width - trackbar.GetWidth() });
	layout.SetRowGap(1);
	layout.SetDefaultRowSize(30);
}

std::vector<TableElement*> ListBox::GetElements()
{
	return behavior.GetElements();
}

void ListBox::CreateListElement(std::wstring name, std::any value)
{
	behavior.CreateListElement(name, value);
}

void ListBox::Add(Component& component)
{
	layout.Add(component);
}

std::any ListBox::GetDragContent()
{
	return behavior.GetDragContent();
}

void ListBox::NotifyOnDragStart(EventOnDragInfo e)
{
	dragManager.NotifyOnDragStart(e);
}

void ListBox::NotifyOnDragEnd(EventOnDragInfo e)
{
	dragManager.NotifyOnDragEnd(e);
}

void ListBox::AddOnDragSubscriber(DragSubscriber& subscriber)
{
	dragManager.AddOnDragSubscriber(subscriber);
}

void ListBox::RemoveOnDragSubscriber(DragSubscriber& subscriber)
{
	dragManager.RemoveOnDragSubscriber(subscriber);
}

void ListBox::NotifyOnDrop(EventOnDragInfo e)
{
	dragManager.NotifyOnDrop(e);
}

void ListBox::AddOnDropSubscriber(DropSubscriber& subscriber)
{
	dragManager.AddOnDropSubscriber(subscriber);
}

void ListBox::RemoveOnDropSubscriber(DropSubscriber& subscriber)
{
	dragManager.RemoveOnDropSubscriber(subscriber);
}
