#include "Component.h"
#include "WindowFrame.h"
#include "CoreWindowFrame.h"

void Component::Add(Component* component)
{
	components->push_back(component);
	component->SetParent(this);
	component->UpdateComponent();
	dynamic_cast<WindowFrame*>(GetRoot())->UpdateWindow();
	OnAddListener* root = dynamic_cast<OnAddListener*>(component->GetRoot());
	if (root)
		component->AddOnAddListener(root);
	NotifyOnAddListeners(*component);
}

Component::Component()
{
	components = new vector<Component*>();
	OnAddListeners = new vector<OnAddListener*>();
	parent = NULL;
	root = NULL;
	backgroundcolor = Color(255, 255, 255);
}

void Component::NotifyOnAddListeners(Component& component)
{
	for (OnAddListener* i : *OnAddListeners)
		i->OnAdd(component);
}

void Component::SetParent(Component * parent)
{
	this->parent = parent;
}

Component* Component::GetRoot()
{
	Component* root = GetParent();
	if (root == NULL)
		return this;
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

void Component::AddOnAddListener(OnAddListener* listener)
{
	OnAddListeners->push_back(listener);
}

void Component::UpdateComponent()
{
	SetPosition(pos.X, pos.Y);
}

void Component::SetPosition(int x, int y)
{
	if (parent == NULL)
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
	this->backgroundcolor = color;
}
