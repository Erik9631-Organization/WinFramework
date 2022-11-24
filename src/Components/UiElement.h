/**
* Class responsibility is to generate resize events, position change events, onHover events and onAction evenets.
  The class acts as an observer and is a composite for the class Shape and class Vgraphics
*/
#pragma once
#include <vector>
#include <string>
#include "DefaultMultiTree.h"
#include "DefaultMove.h"
#include "DefaultResize.h"
#include "api/RenderCommander.h"
#include "DefaultRender.h"
#include "Viewport.h"
#include "api/Viewable.h"
#include "UpdateSubscriber.h"
#include "DefaultActivate.h"
#include "api/Collidable.h"
#include "api/MouseInteractable.h"
#include "DefaultMouseBehavior.h"
#include "DefaultKeyStateBehavior.h"
#include "AccessTools.h"
#include "AddSubject.h"
#include "TickSubject.h"
#include "OnTickSubscriber.h"
#include "Presenter.h"
#include "KeyStateSubject.h"


class EventInfo;
class AddEventInfo;
class EventMoveInfo;
class EventResizeInfo;
class EventHoverInfo;

class UiElement : virtual public Adjustable,
    public virtual RenderCommander,
    public virtual Viewable,
    public virtual MouseInteractable,
    public virtual KeyStateSubject,
    public virtual AddSubject<std::unique_ptr<UiElement>>,
    public virtual TickSubject
{
private:
	void UpdateSubNodes(EventUpdateInfo e);
    std::mutex addToContainerMutex;
protected:
	std::string componentType;
	std::string name;
	DefaultMultiTree<std::unique_ptr<UiElement>>* uiElementNode;
	DefaultRender renderBehavior;
	DefaultMove<std::unique_ptr<UiElement>> moveBehavior;
	DefaultMouseBehavior<MultiTree<std::unique_ptr<UiElement>> &> mouseHandler;
	DefaultKeyStateBehavior keyStateBehavior;
	DefaultResize resizeBehavior;
	DefaultActivate activateBehavior;
	Viewport viewport;
	std::wstring text;
	bool ignoreTranslate = false;
	std::vector<OnTickSubscriber*> tickSubscribers;
    //Used to check for a special case where there is no parent and UiElementNode was already deleted to prevent cyclic
    //Deletion
    bool deletedElementNode = false;
public:
	UiElement();
	UiElement(std::string name);
	UiElement(float x, float y, float width, float height, std::string name);
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
	UiElement& GetRoot();
	glm::vec2 GetSize() override;
	glm::vec2 GetPosition() override;
	float GetWidth() override;
	float GetHeight() override;
	float GetX() override;
	
	/**
	 * Gets the current node within the containment hierarchy
	 * \return returns a node within the Tree of the containment hierarchy.
	 */
    MultiTree<std::unique_ptr<UiElement>> & GetUiElementNode();
	float GetY() override;

	/**
	 * Gets the pointer to the parent of this component
	 * \return returns pointer of the parent component.
	 */
	UiElement * GetParent();
	void SetSize(float width, float height, bool emit) override;
	void SetSize(glm::vec2 size, bool emit) override;
	
	/**
	 * \deprecated use AddOnResizeSubscriber instead
	 */
	void AddOnResizeListener(ResizeSubscriber& listener);
	
	/**
	 * Returns meta information about the component type
	 * \return returns string containing the information about the type of the component. 
	 */
    std::string GetComponentType();
	
	/**
	 * Returns the name of the component.
	 * \return returns string containing the name of the component
	 */
    std::string GetComponentName();

	/**
	 * Sets the name of the component
	 * \param name string containing the name of the component
	 */
	void SetComponentName(std::string name);

	virtual void SetPosition(float x, float y, bool emit) override;
	virtual void SetPosition(glm::vec2 pos, bool emit) override;

	/**
	 * Adds a new uiElement to the containment hierarchy. A uiElement that wants to be displayed has to be within a hierarchy that contains a window.
	 * \param uiElement the uiElement to be added
	 */
	virtual void Add(std::unique_ptr<UiElement> uiElement);
	
	template <typename type, typename ... Args>
	type& Create(Args  ... args)
	{
		std::unique_ptr<type> instance = std::make_unique(args ...);
		auto ref = instance;
		uiElementNode->Add(instance);
		return ref;
	}

	virtual ~UiElement();
	


	// Inherited via Movable
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(EventMoveInfo event) override;
	virtual void SetX(float x, bool emit) override;
	virtual void SetY(float y, bool emit) override;
	virtual float GetAbsoluteX() override;
	virtual float GetAbsoluteY() override;
	virtual glm::vec2 GetAbsolutePosition() override;

	// Inherited via Renderable
	virtual void OnRenderSync(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderCommander(RenderCommander &renderable) override;
	virtual void RemoveRenderCommander(RenderCommander& renderable) override;

	// Inherited via Resizable
	virtual void NotifyOnResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void SetWidth(float width, bool emit) override;
	virtual void SetHeight(float height, bool emit) override;

	// Inherited via Renderable
	virtual std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;

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
	virtual void SetViewportOffset(glm::vec2 offset) override;
	virtual int GetViewportAbsoluteX() override;
	virtual int GetViewportAbsoluteY() override;
	virtual glm::vec2 GetViewportAbsolutePosition() override;
	virtual int GetViewportX() override;
	virtual int GetViewportY() override;
	virtual glm::vec2 GetViewportPosition() override;
	virtual void NotifyOnViewportResizeSubscribers(EventResizeInfo event) override;
	virtual void AddOnViewportResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual void RemoveOnViewportResizeSubscriber(ResizeSubscriber& subscriber) override;
	virtual int GetViewportWidth() override;
	virtual int GetViewportHeight() override;
	virtual void SetViewportSize(glm::vec2 size) override;
	virtual void SetViewportSize(int width, int height) override;
	virtual void SetViewportWidth(int width) override;
	virtual void SetViewportHeight(int height) override;
	virtual glm::vec2 GetViewportSize() override;

	// Inherited via Viewable
	virtual int GetViewportAbsoluteWidth() override;
	virtual int GetViewportAbsoluteHeight() override;
	virtual glm::vec2 GetViewportAbsoluteSize() override;

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
	virtual bool ColidesWithPoint(glm::vec2 point) override;

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
		for (RenderCommander& renderable : GetRenderables())
		{
			AccessTools::Invoke<void>(name, renderable, args ...);
		}
		//Repaint();

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
		for (RenderCommander& renderable : GetRenderables())
		{
			return AccessTools::Invoke<returnType>(name, renderable, args ...);
		}
	}

	// Inherited via MouseInteractable
	virtual std::any ColidesWithUpmost(glm::vec2 point) override;

	// Inherited via KeyStateSubject
	virtual void NotifyOnKeyDown(EventKeyStateInfo e) override;
	virtual void NotifyOnKeyUp(EventKeyStateInfo e) override;
	virtual void NotifyOnKeyPressed(EventKeyStateInfo e) override;
	virtual void AddKeyStateSubscriber(KeyStateSubscriber& subscriber) override;
	virtual void RemoveKeyStateSubscriber(KeyStateSubscriber& subscriber) override;


	// Inherited via AddSubject
	virtual void NotifyOnAddInfo(EventOnAddInfo<std::unique_ptr<UiElement>> e) override;
	virtual void AddOnAddSubscriber(OnAddSubscriber<std::unique_ptr<UiElement>>& subscriber) override;
	virtual void RemoveOnAddSubscriber(OnAddSubscriber<std::unique_ptr<UiElement>>& subscriber) override;

	// Inherited via Viewable
	virtual void SetTranslate(glm::vec2 offset, bool emit) override;
	virtual void SetTranslateX(float x, bool emit) override;
	virtual void SetTranslateY(float Y, bool emit) override;

	// Inherited via Adjustable
	virtual glm::vec2 GetTranslate() override;
	virtual float GetTranslateX() override;
	virtual float GetTranslateY() override;
	
	/**
	 * Gets the internal position of the child components
	 * \return returns the point that contains X and Y of the internal position.
	 */
    glm::vec2 GetChildrenTranslate();
	
	/**
	 * Sets the position of all the subcomponents that are owned by this component at once
	 * \param internalOffset the position
	 */
	void SetChildrenTranslate(glm::vec2 internalOffset);

    void NotifyOnMouseCapture(EventMouseStateInfo e) override;

    bool IsMouseCaptured() override;

    void SetMouseCaptured(bool state) override;
    void OnSync(const DrawData &data) override;
	void AddOnTickSubscriber(OnTickSubscriber *subscriber) override;
	void RemoveOnTickSubscriber(OnTickSubscriber *subscriber) override;
	void NotifyOnTick() override;

    void SetPosition(glm::vec2 position) override;

    void SetPosition(float x, float y) override;

    void SetX(float x) override;

    void SetY(float y) override;

    void SetTranslate(glm::vec2 offset) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y) override;

    void SetSize(glm::vec2 size) override;

    void SetSize(float width, float height) override;

    void SetWidth(float width) override;

    void SetHeight(float height) override;
};