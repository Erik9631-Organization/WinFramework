/**
* Class responsibility is to generate resize events, position change events, onHover events and onAction evenets.
  The class acts as an observer and is a composite for the class Shape and class Vgraphics
*/
#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include "DefaultMultiTree.h"
#include "DefaultMove.h"
#include "DefaultResize.h"
#include "Renderable.h"
#include "DefaultRender.h"
#include "Viewport.h"
#include "Viewable.h"
#include "UpdateSubscriber.h"

class ComponentListener;
class OnAddListener;

class EventInfo;
class AddEventInfo;
class EventMoveInfo;
class EventResizeInfo;
class EventHoverInfo;

using namespace std;
using namespace Gdiplus;
class Component : public Adjustable, public Renderable, public Viewable
{
private:
	void UpdateSubNodes(EventUpdateInfo e);

protected:
	string componentType;
	string name;
	DefaultMultiTree<Component&> componentNode;
	DefaultRender renderBehavior;
	DefaultMove moveBehavior;
	DefaultResize resizeBehavior;
	Viewport viewport;

public:
	Component();
	Component(string name);
	Component(int x, int y, int width, int height, string windowName);
	bool IsRoot();
	Component& GetRoot();
	Size GetSize() override;
	Point GetPosition() override;
	int GetWidth() override;
	int GetHeight() override;
	int GetX() override;
	DefaultMultiTree<Component&>& GetComponentNode();
	int GetY() override;
	Component * GetParent();
	virtual void SetSize(int width, int height) override;
	virtual void SetSize(Size size) override;
	void AddOnResizeListener(ResizeSubscriber& listener);
	string GetComponentType();
	string GetComponentName();
	void SetComponentName(string name);


	virtual void SetPosition(int x, int y);
	virtual void SetPosition(Point pos);

	virtual void Add(Component& component);
	virtual ~Component(){};

	// Inherited via Movable
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	virtual void SetX(int x) override;
	virtual void SetY(int y) override;
	virtual int GetAbsoluteX() override;
	virtual int GetAbsoluteY() override;
	virtual Gdiplus::Point GetAbsolutePosition() override;

	// Inherited via Renderable
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;

	// Inherited via Resizable
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void SetWidth(int width) override;
	virtual void SetHeight(int height) override;

	// Inherited via Renderable
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;

	// Inherited via Viewable
	virtual void AddOnViewportMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnViewportMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnViewportMoveSubscribers(EventMoveInfo event) override;
	virtual void SetViewportXMultiplier(float x) override;
	virtual void SetViewportYMultiplier(float y) override;
	virtual void SetViewportWidthMultiplier(float width) override;
	virtual void SetViewportHeightMultiplier(float height) override;
	virtual float GetViewportXMultiplier() override;
	virtual float GetViewportYMultiplier() override;
	virtual float GetViewportWidthMultiplier() override;
	virtual float GetViewportHeightMultiplier() override;
	virtual void SetViewportXOffset(int x) override;
	virtual void SetViewportYOffset(int y) override;
	virtual void SetViewportOffset(Gdiplus::Point offset) override;
	virtual int GetViewportAbsoluteX() override;
	virtual int GetViewportAbsoluteY() override;
	virtual Gdiplus::Point GetViewportAbsolutePosition() override;
	virtual int GetViewportX() override;
	virtual int GetViewportY() override;
	virtual Gdiplus::Point GetViewportPosition() override;
	virtual void NotifyOnViewportResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnViewportResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnViewportResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual int GetViewportWidth() override;
	virtual int GetViewportHeight() override;
	virtual void SetViewportSize(Gdiplus::Size size) override;
	virtual void SetViewportSize(int width, int height) override;
	virtual void SetViewportWidth(int width) override;
	virtual void SetViewportHeight(int height) override;
	virtual Gdiplus::Size GetViewportSize() override;

	// Inherited via Viewable
	virtual int GetViewportAbsoluteWidth() override;
	virtual int GetViewportAbsoluteHeight() override;
	virtual Gdiplus::Size GetViewportAbsoluteSize() override;

	// Inherited via UpdateSubscriber
	virtual void OnUpdate(EventUpdateInfo e) override;
};