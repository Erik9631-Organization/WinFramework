/**
* Class responsibility is to generate resize events, viewPortSize change events, onHover events and onAction evenets.
  The class acts as an observer and is a composite for the class Shape and class Vgraphics
*/
#pragma once
#include <vector>
#include <string>
#include "DefaultMultiTree.h"
#include "UiMoveBehavior.h"
#include "DefaultResize.h"
#include "RenderCommander.h"
#include "DefaultRender.h"
#include "ModelViewport.h"
#include "Viewable.h"
#include "UpdateSubscriber.h"
#include "DefaultActivate.h"
#include "Collidable.h"
#include "MouseInteractable.h"
#include "DefaultMouseBehavior.h"
#include "DefaultKeyStateBehavior.h"
#include "AccessTools.h"
#include "AddSubject.h"
#include "TickSubject.h"
#include "OnTickSubscriber.h"
#include "Presenter.h"
#include "KeyStateSubject.h"
#include "MountedSubject.h"


class EventInfo;
class AddEventInfo;
class EventMoveInfo;
class EventResizeInfo;
class EventHoverInfo;

class UiElement : virtual public Adjustable,
    public virtual RenderCommander,
    public virtual MouseInteractable,
    public virtual KeyStateSubject,
    public virtual AddSubject<std::unique_ptr<UiElement>>,
    public virtual TickSubject,
    public virtual MountedSubject,
    public virtual MountedSubscriber,
    public virtual Viewport2
{
private:
	void UpdateSubNodes(EventUpdateInfo e);
    std::mutex addToContainerMutex;
protected:
	std::string componentType;
	std::string name;
	DefaultMultiTree<std::unique_ptr<UiElement>>* uiElementNode;
	DefaultRender renderBehavior;
	UiMoveBehavior<std::unique_ptr<UiElement>> moveBehavior;
	DefaultMouseBehavior<MultiTree<std::unique_ptr<UiElement>> &> mouseHandler;
    std::vector<MountedSubscriber*>mountedSubscribers;
	DefaultKeyStateBehavior keyStateBehavior;
	DefaultResize resizeBehavior;
	DefaultActivate activateBehavior;
	ModelViewport viewport;
	std::wstring text;
	bool ignoreTranslate = false;
	std::vector<OnTickSubscriber*> tickSubscribers;
    Presenter* presenter = nullptr;
    //Used to check for a special case where there is no parent and UiElementNode was already deleted to prevent cyclic
    //Deletion
    bool deletedElementNode = false;
public:
	UiElement();
	explicit UiElement(std::string name);
	UiElement(float x, float y, float width, float height, std::string name);
    Presenter* GetPresenter();


	/**
	 * Returns the text value of the component. (Usually used for name or description)
	 * \return returns unicode string value
	 */
	virtual const std::wstring & GetText();

    //TODO UI element doesn't have text. Only tag. Should be moved to individual interfaces
	/**
	 * Sets the text value of the component. (Usually used for name or description)
	 * \param text sets the unicode text value of the component.
	 */
	virtual void SetText(std::wstring text);

	/**
	 * Sets whether the component should ignore values set by SetTranslate, SetTranslateX, SetTranslateY
	 * \param ignoreTranslate true for ignoring the viewPortSize, false for not ignoring the viewPortSize
	 */
	void SetIgnoreTranslate(bool ignoreTranslate);
	
	/**
	 * Sets whether the component should ignore values set by SetTranslate, SetTranslateX, SetTranslateY
	 * \param ignoreOffset true for ignoring the viewPortSize, false for not ignoring the viewPortSize
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
	const glm::vec4 & GetSize() override;
	const glm::vec4 & GetPosition() const override;
	float GetWidth() override;
	float GetHeight() override;

	/**
	 * Gets the current node within the containment hierarchy
	 * \return returns a node within the Tree of the containment hierarchy.
	 */
    MultiTree<std::unique_ptr<UiElement>> & GetUiElementNode();

	/**
	 * Gets the pointer to the parent of this component
	 * \return returns pointer of the parent component.
	 */
	UiElement * GetParent();
	void SetSize(float width, float height, bool emit) override;
	void SetSize(const glm::vec4 &size, bool emit) override;
	
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

    void SetPosition(const glm::vec4 &pos, bool emit = true) override;

	/**
	 * Adds a new uiElement to the containment hierarchy. A uiElement that wants to be displayed has to be within a hierarchy that contains a window.
	 * \param uiElement the uiElement to be added
	 */
	virtual UiElement & Add(std::unique_ptr<UiElement> uiElement);
	
	template <typename type, typename ... Args>
	type& CreateElement(Args  ... args)
	{
		std::unique_ptr<type> instance = std::make_unique<type>(std::forward<Args>(args) ...);
		auto& ref = *instance;
		Add(std::move(instance));
		return ref;
	}

	virtual ~UiElement();

    // Inherited via Activatable
    void AddOnActivateSubscriber(ActivateSubscriber& subscriber) override;
    void RemoveOnActivateSubscriber(ActivateSubscriber& subscriber) override;
    void NotifyOnActivateStateChanged(EventOnActivateInfo& activateInfo) override;
    virtual void SetActive(bool state) override;
    virtual bool IsActive() override;
	


	// Inherited via Movable
	virtual void AddOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void RemoveOnMoveSubscriber(MoveSubscriber& subscriber) override;
	virtual void NotifyOnMoveSubscribers(const EventMoveInfo &event) override;
	virtual const glm::vec4 & GetAbsolutePosition() const override;

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
	// Inherited via UpdateSubscriber
	virtual void OnUpdate(EventUpdateInfo e) override;

	// Inherited via MouseStateSubject
	virtual void NotifyOnMouseDown(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseUp(EventMouseStateInfo e) override;
	virtual void NotifyOnMousePressed(EventMouseStateInfo e) override;
	virtual void NotifyOnMouseHover(EventMouseStateInfo e) override;
	virtual void AddMouseStateSubscriber(MouseStateSubscriber& subscriber) override;
	virtual void RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber) override;

	// Inherited via Collidable
	virtual bool ColidesWithPoint(glm::vec4 point) override;

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
	virtual std::any ColidesWithUpmost(glm::vec4 point) override;

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
    void SetTranslate(const glm::vec4 &offset, bool emit = true) override;

	// Inherited via Adjustable
	virtual const glm::vec4 & GetTranslate() const override;
	
	/**
	 * Gets the internal viewPortSize of the child components
	 * \return returns the point that contains X and Y of the internal viewPortSize.
	 */
    glm::vec4 GetChildrenTranslate();
	
	/**
	 * Sets the viewPortSize of all the subcomponents that are owned by this component at once
	 * \param internalOffset the viewPortSize
	 */
	void SetChildrenTranslate(glm::vec4 internalOffset);

    void NotifyOnMouseCapture(EventMouseStateInfo e) override;

    bool IsMouseCaptured() override;

    void SetMouseCaptured(bool state) override;
    void OnSync(const DrawData &data) override;
	void AddOnTickSubscriber(OnTickSubscriber *subscriber) override;
	void RemoveOnTickSubscriber(OnTickSubscriber *subscriber) override;
	void NotifyOnTick() override;

    void SetSize(glm::vec4 size) override;

    void SetSize(float width, float height) override;

    void SetWidth(float width) override;

    void SetHeight(float height) override;

    void AddOnMountedSubscriber(MountedSubscriber &subscriber) override;

    void RemoveOnMountedSubscriber(MountedSubscriber &subscriber) override;

    void NotifyOnMounted(Presenter &presenter) override;

    /**
    * Called by the TopMost component added to the Presenter to notify the others that they have a presenter.
    */
    void OnMounted(Presenter &presenter, UiElement& element) override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec4 &vec4) override;

    const glm::vec4 & GetViewportSize() override;

    const glm::vec4 & GetViewportPosition() override;

    void ResetViewport() override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;
};