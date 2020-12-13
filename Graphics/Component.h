#pragma once
#include "IDrawable.h"
#include <vector>
#include "OnAddListener.h"
#include <string>
using namespace std;
class Component : IDrawable
{
protected:
	void NotifyOnAddListeners(Component& component);
	void UpdateComponent();
	vector<Component*>*components;
	vector<OnAddListener*>*OnAddListeners;
	Component* parent;
	Component* root;
	Graphics* graphics;
	Point pos;
	Size size;
	string componentName;
	Color backgroundcolor;

public:
	void SetParent(Component * parent);
	Component* GetRoot();
	Size GetSize();
	Point GetPosition();
	int GetWidth();
	int GetHeight();
	int GetX();
	int GetY();
	Component * GetParent();
	virtual void SetSize(int width, int height);
	virtual void SetSize(Size size);
	void AddOnAddListener(OnAddListener* listener); 
	virtual void Paint(Graphics& graphics);
	Graphics* GetGraphics();
	string GetComponentType();


	virtual void SetPosition(int x, int y);
	virtual void SetPosition(Point pos);
	void SetBackgroundColor(Color color);
	void GetBackgroundColor();

	virtual void Add(Component* component);
	Component();
	virtual ~Component(){};
};