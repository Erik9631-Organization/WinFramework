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
#include "DefaultActivate.h"
#include "Collidable.h"
#include "MouseInteractable.h"
#include "DefaultMouseBehavior.h"
#include "DefaultKeyStateBehavior.h"
#include "AccessTools.h"
#include "AddSubject.h"


class EventInfo;
class AddEventInfo;
class EventMoveInfo;
class EventResizeInfo;
class EventHoverInfo;

using namespace std;
using namespace Gdiplus;
class Component : public Adjustable, public Renderable, public Viewable, public MouseInteractable, public KeyStateSubject, public AddSubject<Component&>
{
private:
	void UpdateSubNodes(EventUpdateInfo e);
protected:
	string componentType;
	string name;
	DefaultMultiTree <Component&> componentNode;
	DefaultRender renderBehavior;
	DefaultMove<Component&> moveBehavior;
	DefaultMouseBehavior<MultiTree<Component&>&> mouseHandler;
	DefaultKeyStateBehavior keyStateBehavior;
	DefaultResize resizeBehavior;
	DefaultActivate activateBehavior;
	Viewport viewport;
	std::wstring text;
	bool ignoreTranslate = false;
public:

	Component();
	Component(string name);
	Component(int x, int y, int width, int height, string windowName);
	/**
	 * Returns the text value of the component. (Usually used for name or description)
	 * \return returns unicode string value
	 */
	virtual std::wstring GetText();
	
	/**
	 * Sets the text value of the component. (Usually used for name or description)
	 * \param text sets the unicode text value of the component.
	 */
	virtual void SetText(std::wstring text);

	/**
	 * Sets whether the component should ignore values set by SetTranslate, SetTranslateX, SetTranslateY
	 * \param ignoreTranslate true for ignoring the position, false for not ignoring the position
	 */
	void SetIgnoreTranslate(bool ignoreTranslate);
	
	/**
	 * Sets whether the component should ignore values set by SetTranslate, SetTranslateX, SetTranslateY
	 * \param ignoreOffset true for ignoring the position, false for not ignoring the position
	 */
	bool IsIgnoringTranslate();

	/**
	 * Returns whether the component is at the top of the containment hierarchy
	 * \return returns true if it is at the top of the containment hierarchy, otherwise returns false.
	 */
	bool IsRoot();

	/**
	 * Returns the component at the top of the containment hierarchy
	 * \return returns reference to the component at the top of the containment hierarchy.
	 */
	Component& GetRoot();
	Size GetSize() override;
	Point GetPosition() override;
	int GetWidth() override;
	int GetHeight() override;
	int GetX() override;
	
	/**
	 * Gets the current node within the containment hierarchy
	 * \return returns a node within the Tree of the containment hierarchy.
	 */
	MultiTree<Component&>& GetComponentNode();
	int GetY() override;

	/**
	 * Gets the pointer to the parent of this component
	 * \return returns pointer of the parent component.
	 */
	Component * GetParent();
	void SetSize(int width, int height) override;
	void SetSize(Gdiplus::Size size) override;
	
	/**
	 * \deprecated use AddOnResizeSubscriber instead
	 */
	void AddOnResizeListener(ResizeSubscriber& listener);
	
	/**
	 * Returns meta information about the component type
	 * \return returns string containing the information about the type of the component. 
	 */
	string GetComponentType();
	
	/**
	 * Returns the name of the component.
	 * \return returns string containing the name of the component
	 */
	string GetComponentName();

	/**
	 * Sets the name of the component
	 * \param name string containing the name of the component
	 */
	void SetComponentName(string name);

	virtual void SetPosition(int x, int y);
	virtual void SetPosition(Gdiplus::Point pos);

	/**
	 * Adds a new component to the containment hierarchy. A component that wants to be displayed has to be within a hierarchy that contains a window.
	 * \param component the component to be added 
	 */
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

	// Inherited via Activatable
	virtual void AddOnActivateSubscriber(ActivateSubscriber& subscriber) override;
	virtual void RemoveOnActivateSubscriber(ActivateSubscriber& subscriber) override;
	virtual void NotifyOnActivateStateChanged(EventOnActivateInfo& activateInfo) override;
	virtual void SetActive(bool state) override;
	virtual bool IsActive() override;

	// Inherited via MouseStateSubject
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseUp(EventMouseStateInfo e) override;
	virtual void NotifyOnMousePressed(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseHover(EventMouseStateInfo e) override;
	virtual void AddMouseStateSubscriber(MouseStateSubscriber& subscriber) override;
	virtual void RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber) override;

	// Inherited via Collidable
	virtual bool ColidesWithPoint(Gdiplus::Point) override;

	// Inherited via MouseStateSubject
	virtual void NotifyOnMouseEnter(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseLeave(EventMouseStateInfo e) override;

	// Inherited via MouseInteractable
	virtual bool HasMouseEntered() override;

	/**
	 * Sets the property via the meta object protocol. List of available properties can be found in all classes that implement the Renderable interface.
	 * \param name the property name that should be changed
	 * \param args the arguments of the property that should be changed.
	 * \tparam Args the type of arguments that the property receives (Should be auto resolved by the compiler).
	 */
	template<typename ... Args>
	void SetProperty(std::string name, Args ... args)
	{
		for (Renderable& renderable : GetRenderables())
		{
			AccessTools::Invoke<void>(name, renderable, args ...);
		}
		Repaint();

	}

	/**
	 * Get the property via the meta object protocol. List of available properties can be found in all classes the implement the Renderable interface.
	 * \param name the property name the value of which you want returned.
	 * \param args the arguments of the property.
	 * \tparam Args the type of arguments that the property receives (Should be auto resolved by the compiler).
	 */
	template<typename returnType, typename ... Args>
	returnType GetPropery(std::string name, Args ... args)
	{
		for (Renderable& renderable : GetRenderables())
		{
			return AccessTools::Invoke<returnType>(name, renderable, args ...);
		}
	}

	// Inherited via MouseInteractable
	virtual std::any ColidesWithUpmost(Gdiplus::Point) override;

	// Inherited via KeyStateSubject
	virtual void NotifyOnKeyDown(EventKeyStateInfo e) override;
	virtual void NotifyOnKeyUp(EventKeyStateInfo e) override;
	virtual void NotifyOnKeyPressed(EventKeyStateInfo e) override;
	virtual void AddKeyStateSubscriber(KeyStateSubscriber& subscriber) override;
	virtual void RemoveKeyStateSubscriber(KeyStateSubscriber& subscriber) override;


	// Inherited via AddSubject
	virtual void NotifyOnAddInfo(EventOnAddInfo<Component&> e) override;
	virtual void AddOnAddSubscriber(OnAddSubscriber<Component&>& subscriber) override;
	virtual void RemoveOnAddSubscriber(OnAddSubscriber<Component&>& subscriber) override;

	// Inherited via Viewable
	virtual void SetTranslate(Gdiplus::Point offset) override;
	virtual void SetTranslateX(int x) override;
	virtual void SetTranslateY(int Y) override;

	// Inherited via Adjustable
	virtual Gdiplus::Point GetTranslate() override;
	virtual int GetTranslateX() override;
	virtual int GetTranslateY() override;
	
	/**
	 * Gets the internal position of the child components
	 * \return returns the point that contains X and Y of the internal position.
	 */
	Gdiplus::Point GetChildrenTranslate();
	
	/**
	 * Sets the position of all the subcomponents that are owned by this component at once
	 * \param internalOffset the position
	 */
	void SetChildrenTranslate(Gdiplus::Point internalOffset);

    void NotifyOnMouseCapture(EventMouseStateInfo e) override;

    bool IsMouseCaptured() override;

    void SetMouseCaptured(bool state) override;
};