/**
* Class responsibility is to generate resize events, position change events, onHover events and onAction evenets.
  The class acts as an observer and is a composite for the class Shape and class Vgraphics
*/
#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>
class ComponentListener;
class OnAddListener;

class EventInfo;
class AddEventInfo;
class EventMoveInfo;
class EventResizeInfo;
class EventHoverInfo;

using namespace std;
using namespace Gdiplus;
class Component
{
protected:
	vector<reference_wrapper<Component>>components;
	Component* parent;
	Component* root;
	Graphics* graphics;
	Point pos;
	Size size;
	string componentName;
	Color backgroundColor;

	//Listeners
	vector<reference_wrapper<ComponentListener>>ComponentListeners;
	vector<reference_wrapper<OnAddListener>>onAddListeners; //Will be changed later to delegate to VectorContainer.Add event. Used for testing.
	vector<reference_wrapper<OnMoveListeners>>onAddListeners;

	void NotifyOnAddListeners(AddEventInfo& eventInfo);
	void NotifyComponentListeners(EventInfo& eventInfo);
	void NotifyOnMoveListeners(EventMoveInfo& eventInfo);
	void NotifyOnResizeListeners(EventResizeInfo& eventInfo);
	void NotifyOnHoveListeners(EventResizeInfo& eventInfo);


	void UpdateComponent();

public:
	void SetParent(Component * parent);
	bool IsRoot();
	Component& GetRoot();
	Size GetSize();
	Point GetPosition();
	int GetWidth();
	int GetHeight();
	int GetX();
	int GetY();
	Component * GetParent();
	virtual void SetSize(int width, int height);
	virtual void SetSize(Size size);
	void AddOnAddListener(OnAddListener & listener); 
	void AddOnResizeListener(ComponentListener& listener);
	virtual void Paint(Graphics& graphics);
	Graphics* GetGraphics();
	string GetComponentType();


	virtual void SetPosition(int x, int y);
	virtual void SetPosition(Point pos);
	void SetBackgroundColor(Color color);
	void GetBackgroundColor();

	virtual void Add(Component& component);
	Component();
	virtual ~Component(){};
};