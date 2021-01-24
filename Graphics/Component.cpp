#include "Component.h"
#include "WindowFrame.h"
#include "CoreWindowFrame.h"
#include "OnAddListener.h"
#include "AddEventInfo.h"
#include "EventMoveInfo.h"
#include "ComponentListener.h"
#include "EventResizeInfo.h"

void Component::Add(Component& component)
{
	component.UpdateComponent();
	componentNode.Add(component.GetComponentNode());
	NotifyOnAddListeners(AddEventInfo(component));
}

Component::Component() : componentNode(*this)
{
	parent = NULL;
	root = NULL;
	backgroundColor = Color(255, 255, 255);
}

void Component::NotifyOnAddListeners(AddEventInfo& eventInfo)
{
	for (OnAddListener& i : onAddListeners)
		i.OnAdd(eventInfo);
}

void Component::NotifyOnMoveListeners(EventMoveInfo & eventInfo)
{
	for (ComponentListener& i : ComponentListeners)
		i.OnMove(eventInfo);
}

void Component::NotifyOnResizeListeners(EventResizeInfo & eventInfo)
{
	for (ComponentListener& i : ComponentListeners)
		i.OnResize(eventInfo);
}

bool Component::IsRoot()
{
	return componentNode.IsRoot();
}

Component& Component::GetRoot()
{
	return componentNode.GetRoot().GetValue();
}

void Component::Paint(Graphics& graphics)
{
	CoreWindowFrame::ConsoleWrite("Painting: " + componentType);
}

Graphics * Component::GetGraphics()
{
	return graphics;
}

string Component::GetComponentType()
{
	return componentType;
}

string Component::GetComponentName()
{
	return name;
}

void Component::SetComponentName(string name)
{
	this->name = name;
}

Size Component::GetSize()
{
	return size;
}

Point Component::GetPosition()
{
	return pos;
}

int Component::GetWidth()
{
	return size.Width;
}

int Component::GetHeight()
{
	return size.Height;
}

int Component::GetX()
{
	return pos.X;
}

DefaultMultiTree<Component&>& Component::GetComponentNode()
{
	return componentNode;
}

int Component::GetY()
{
	return pos.Y;
}

Component * Component::GetParent()
{
	if (componentNode.GetParent() == nullptr)
		return nullptr;
	return (Component*)&componentNode.GetParent()->GetValue();
}

void Component::SetSize(int width, int height)
{
	size.Width = width;
	size.Height = height;
}

void Component::SetSize(Size size)
{
	this->size = size;
}

void Component::AddOnAddListener(OnAddListener& listener)
{
	onAddListeners.push_back(listener);
}


void Component::UpdateComponent()
{
	SetPosition(pos.X, pos.Y);
}

void Component::SetPosition(int x, int y)
{
	Component& root = this->GetRoot();
	if (this->IsRoot() || this->GetParent() == &root)
	{
		pos.X = x;
		pos.Y = y;
		return;
	}
	pos.X = x + parent->GetX();
	pos.Y = y + parent->GetY();

}

void Component::SetPosition(Point pos)
{
	this->pos = pos;
}

void Component::SetBackgroundColor(Color color)
{
	this->backgroundColor = color;
}
