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
	components.push_back(component);
	component.SetParent(this);
	component.UpdateComponent();
	if (!IsRoot())
	{
		Component& rootComponent = this->GetRoot();
		rootComponent.Add(component);
	}
	NotifyOnAddListeners(AddEventInfo(component));
}

Component::Component()
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

void Component::SetParent(Component * parent)
{
	this->parent = parent;
}

bool Component::IsRoot()
{
	if (this->GetParent() == nullptr)
		return true;
	else
		return false;

}

Component& Component::GetRoot()
{
	Component* root = GetParent();
	if (root == NULL)
		return *this;
	else
		return root->GetRoot();
}

void Component::Paint(Graphics& graphics)
{
	CoreWindowFrame::ConsoleWrite("Painting: " + componentName);
}

Graphics * Component::GetGraphics()
{
	return graphics;
}

string Component::GetComponentType()
{
	return componentName;
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

int Component::GetY()
{
	return pos.Y;
}

Component * Component::GetParent()
{
	return parent;
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
