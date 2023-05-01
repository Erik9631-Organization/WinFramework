#include "UiElement.h"
#include "Window.h"
#include "EventUpdateInfo.h"
#include "DrawData2D.h"
#include <execution>
#include <algorithm>
#include "WindowsCore.h"
using namespace std;
//TODO Refactor movement. Incorporate z into the calculations

UiElement & UiElement::Add(std::unique_ptr<UiElement> uiElement)
{
    auto& elementRef = *uiElement.release();;
    auto root = dynamic_cast<Window*>(&GetRoot());
    //We always draw the added element on top of the current element(The parent)

    std::unique_ptr<MultiTree<std::unique_ptr<UiElement>>> nodeToBeAdded {&elementRef.GetUiElementNode()};
    uiElementNode->AddNode(std::move(nodeToBeAdded));

    //RegisterComponent to the memory manager
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw)); //Recalculate offsets based on the current parent

    if(root != nullptr)
        elementRef.NotifyOnMounted(static_cast<Presenter&>(*root));

    return elementRef;
}

UiElement::UiElement() : UiElement(0, 0, 0, 0, "")
{

}

UiElement::UiElement(string name) : UiElement(0, 0, 0, 0, name)
{

}

UiElement::UiElement(float x, float y, float width, float height, string name) :
         uiElementNode(new DefaultMultiTree(std::unique_ptr<UiElement>(this))),
	moveBehavior(*uiElementNode),
	mouseHandler(*uiElementNode),
	renderBehavior(*this),
	keyStateBehavior(*this),
	resizeBehavior(*this)
{
    moveBehavior.SetPosition({x, y, 0});
    resizeBehavior.SetSize({width, height, 0});
	this->name = name;
}

const wstring & UiElement::GetText()
{
	return text;
}

void UiElement::SetText(std::wstring text)
{
	this->text = text;
}

void UiElement::SetIgnoreTranslate(bool ignoreTranslate)
{
	this->ignoreTranslate = ignoreTranslate;
}

bool UiElement::IsIgnoringTranslate()
{
	return ignoreTranslate;
}

void UiElement::AddOnMoveSubscriber(MoveSubscriber& subscriber)
{
	moveBehavior.AddOnMoveSubscriber(subscriber);
}

void UiElement::RemoveOnMoveSubscriber(MoveSubscriber& subscriber)
{
	moveBehavior.RemoveOnMoveSubscriber(subscriber);
}

void UiElement::NotifyOnMoveSubscribers(const EventMoveInfo &event)
{
	moveBehavior.NotifyOnMoveSubscribers(event);
}

void UiElement::OnRenderSync(RenderEventInfo e)
{
    renderBehavior.OnRenderSync(e);
}

void UiElement::OnSync(const DrawData &data)
{
    auto parentPos = glm::vec3(0, 0, 0);

    if(!IsRoot())
    {
        parentPos.x = GetPosition().x;
        parentPos.y = GetPosition().y;
    }

    DrawData2D drawData{parentPos, GetSize()};
    renderBehavior.OnSync(drawData);
}

void UiElement::Repaint()
{
	if (IsRoot())
		return;
	GetRoot().Repaint();
}

void UiElement::AddRenderCommander(RenderCommander &renderable)
{
    renderBehavior.AddRenderCommander(renderable);
}

void UiElement::RemoveRenderCommander(RenderCommander& renderable)
{
    renderBehavior.RemoveRenderCommander(renderable);
}

void UiElement::NotifyOnResizeSubscribers(EventResizeInfo event)
{
	resizeBehavior.NotifyOnResizeSubscribers(event);
}

void UiElement::AddOnResizeSubscriber(ResizeSubscriber& subscriber)
{
    //CRASH1
	resizeBehavior.AddOnResizeSubscriber(subscriber);
}

void UiElement::RemoveOnResizeSubscriber(ResizeSubscriber& subscriber)
{
	resizeBehavior.RemoveOnResizeSubscriber(subscriber);
}

std::vector<std::reference_wrapper<RenderCommander>> UiElement::GetRenderables()
{
	return renderBehavior.GetRenderables();
}

void UiElement::OnUpdate(EventUpdateInfo e)
{
	moveBehavior.CalculateAbsolutePosition();
	UpdateSubNodes(e);
	if (!e.HasFlag(EventUpdateFlags::Redraw))
		return;
	Repaint();
}

void UiElement::AddOnActivateSubscriber(ActivateSubscriber& subscriber)
{
	activateBehavior.AddOnActivateSubscriber(subscriber);
}

void UiElement::RemoveOnActivateSubscriber(ActivateSubscriber& subscriber)
{
	activateBehavior.RemoveOnActivateSubscriber(subscriber);
}

void UiElement::NotifyOnActivateStateChanged(EventOnActivateInfo& activateInfo)
{
	activateBehavior.NotifyOnActivateStateChanged(activateInfo);
}

void UiElement::SetActive(bool state)
{
	activateBehavior.SetActive(state);
}

bool UiElement::IsActive()
{
	return activateBehavior.IsActive();
}

void UiElement::NotifyOnMouseDown(EventMouseStateInfo e)
{
	mouseHandler.NotifyOnMouseDown(EventMouseStateInfo(e, e.GetMousePosition(), this));
}

void UiElement::NotifyOnMouseUp(EventMouseStateInfo e)
{
	mouseHandler.NotifyOnMouseUp(EventMouseStateInfo(e, e.GetMousePosition(), this));
}

void UiElement::NotifyOnMousePressed(EventMouseStateInfo e)
{
	mouseHandler.NotifyOnMousePressed(EventMouseStateInfo(e, e.GetMousePosition(), this));
}

void UiElement::NotifyOnMouseHover(EventMouseStateInfo e)
{
	mouseHandler.NotifyOnMouseHover(EventMouseStateInfo(e, e.GetMousePosition(), this));
}

void UiElement::AddMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	mouseHandler.AddMouseStateSubscriber(subscriber);
}

void UiElement::RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	mouseHandler.RemoveMouseStateSubscriber(subscriber);
}

bool UiElement::ColidesWithPoint(glm::vec3 point)
{
	if ( !(point.x >= GetAbsolutePosition().x && point.x <= GetAbsolutePosition().x + GetSize().x) )
		return false;
	if ( !(point.y >= GetAbsolutePosition().y && point.y <= GetAbsolutePosition().y + GetSize().y) )
		return false;
	return true;
}

void UiElement::NotifyOnMouseEnter(EventMouseStateInfo e)
{
	mouseHandler.NotifyOnMouseEnter(e);
}

void UiElement::NotifyOnMouseLeave(EventMouseStateInfo e)
{
	mouseHandler.NotifyOnMouseLeave(e);
}

bool UiElement::HasMouseEntered()
{
	return mouseHandler.HasMouseEntered();
}

std::any UiElement::ColidesWithUpmost(glm::vec3 point)
{
	for (int i = 0; i < uiElementNode->GetNodeCount(); i++)
	{
		if (uiElementNode->GetNode(i).GetValue()->ColidesWithPoint(point))
			return std::any_cast<UiElement*>(uiElementNode->GetNode(i).GetValue()->ColidesWithUpmost(point));
	}
	return std::make_any<UiElement*>(this);
}

void UiElement::NotifyOnKeyDown(EventKeyStateInfo e)
{
	keyStateBehavior.NotifyOnKeyDown(e);
}

void UiElement::NotifyOnKeyUp(EventKeyStateInfo e)
{
	keyStateBehavior.NotifyOnKeyUp(e);
}

void UiElement::NotifyOnKeyPressed(EventKeyStateInfo e)
{
	keyStateBehavior.NotifyOnKeyPressed(e);
}

void UiElement::AddKeyStateSubscriber(KeyStateSubscriber& subscriber)
{
	keyStateBehavior.AddKeyStateSubscriber(subscriber);
}

void UiElement::RemoveKeyStateSubscriber(KeyStateSubscriber& subscriber)
{
	keyStateBehavior.RemoveKeyStateSubscriber(subscriber);
}

void UiElement::NotifyOnAddInfo(EventOnAddInfo<unique_ptr<UiElement>> e)
{
	uiElementNode->NotifyOnAddInfo(e);
}

void UiElement::AddOnAddSubscriber(OnAddSubscriber<std::unique_ptr<UiElement>>& subscriber)
{
	uiElementNode->AddOnAddSubscriber(subscriber);
}

void UiElement::RemoveOnAddSubscriber(OnAddSubscriber<std::unique_ptr<UiElement>>& subscriber)
{
	uiElementNode->RemoveOnAddSubscriber(subscriber);
}

void UiElement::SetTranslate(const glm::vec3 &offset, bool emit)
{
	if (ignoreTranslate)
		return;

    moveBehavior.SetTranslate(offset, emit);
}

const glm::vec3 & UiElement::GetTranslate() const
{
    return moveBehavior.GetTranslate();
}

glm::vec3 UiElement::GetChildrenTranslate()
{
	return moveBehavior.GetChildrenTranslate();
}

void UiElement::SetChildrenTranslate(glm::vec4 internalOffset)
{
	if (ignoreTranslate)
		return;
    moveBehavior.TranslateChildren(internalOffset);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
	//Notify the root about sync
}


void UiElement::UpdateSubNodes(EventUpdateInfo e)
{
	e.DisableFlag(EventUpdateFlags::Redraw); //Only the top of the subTree should do redraw
	for (int i = 0; i < uiElementNode->GetNodeCount(); i++)
	{
		std::unique_ptr<UiElement>& node = uiElementNode->Get(i);
		node->OnUpdate(EventUpdateInfo(e));
	}
}

const glm::vec3 & UiElement::GetAbsolutePosition() const
{
	return moveBehavior.GetAbsolutePosition();
}

bool UiElement::IsRoot()
{
	return uiElementNode->IsRoot();
}

UiElement& UiElement::GetRoot()
{
	return *uiElementNode->GetRootNode().GetValue();
}

string UiElement::GetComponentType()
{
	return componentType;
}

string UiElement::GetComponentName()
{
	return name;
}

void UiElement::SetComponentName(string name)
{
	this->name = name;
}

const glm::vec3 & UiElement::GetSize() const
{
	return resizeBehavior.GetSize();
}

const glm::vec3 & UiElement::GetPosition() const
{
	return moveBehavior.GetPosition();
}

MultiTree<std::unique_ptr<UiElement>> & UiElement::GetUiElementNode()
{
	return *uiElementNode;
}

UiElement * UiElement::GetParent()
{
	if (uiElementNode->GetParent() == nullptr)
		return nullptr;
	return uiElementNode->GetParent().get();
}

void UiElement::SetSize(const glm::vec3 &size, bool emit)
{
    resizeBehavior.SetSize(size, emit);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::AddOnResizeListener(ResizeSubscriber& subscriber)
{
	resizeBehavior.AddOnResizeSubscriber(subscriber);
}


void UiElement::SetPosition(const glm::vec3 &pos, bool emit)
{
    moveBehavior.SetPosition(pos, emit);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::NotifyOnMouseCapture(EventMouseStateInfo e)
{
    mouseHandler.NotifyOnMouseCapture(EventMouseStateInfo(e, e.GetMousePosition(), this));
}

bool UiElement::IsMouseCaptured()
{
    return mouseHandler.IsMouseCaptured();
}

void UiElement::SetMouseCaptured(bool state)
{
    mouseHandler.SetMouseCaptured(state);
}

void UiElement::AddOnTickSubscriber(OnTickSubscriber *subscriber)
{
    addToContainerMutex.lock();
    tickSubscribers.push_back(subscriber);
    addToContainerMutex.unlock();
}

void UiElement::RemoveOnTickSubscriber(OnTickSubscriber *subscriber)
{
    for(auto it = tickSubscribers.begin(); it < tickSubscribers.end(); it++)
    {
        if(*it == subscriber)
        {
            tickSubscribers.erase(it);
            return;
        }

    }
}

void UiElement::NotifyOnTick()
{
    addToContainerMutex.lock();
    for(OnTickSubscriber* i : tickSubscribers)
        i->OnTick();

    std::for_each(std::execution::par, tickSubscribers.begin(), tickSubscribers.end(), [&](auto* subscriber)
    {
        subscriber->OnTick();
    });
    addToContainerMutex.unlock();
}

UiElement::~UiElement()
{
    if(IsRoot())
    {
        uiElementNode->Disown(true);
        delete uiElementNode;
    }
}

void UiElement::AddOnMountedSubscriber(MountedSubscriber &subscriber)
{
    mountedSubscribers.push_back(&subscriber);
    if(this->GetPresenter() != nullptr)
        NotifyOnMounted(*this->GetPresenter());
}

void UiElement::RemoveOnMountedSubscriber(MountedSubscriber &subscriber)
{
    for(auto it = mountedSubscribers.begin(); it != mountedSubscribers.end(); it++)
    {
        if(*it == &subscriber)
        {
            mountedSubscribers.erase(it);
            return;
        }
    }
}

void UiElement::NotifyOnMounted(Presenter &presenter)
{
    for(auto subscriber : mountedSubscribers)
        subscriber->OnMounted(presenter, *this);

    for(auto& element : GetUiElementNode().GetNodes())
    {
        element->GetValue()->NotifyOnMounted(presenter);
    }
    this->presenter = &presenter;
    OnMounted(presenter, *this);
}

Presenter *UiElement::GetPresenter()
{
    return presenter;
}


void UiElement::OnMounted(Presenter &presenter, UiElement& element)
{
    this->presenter = &presenter;
}

void UiElement::AddViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewport.AddViewport2Subscriber(subscriber);
}

void UiElement::RemoveViewport2Subscriber(Viewport2Subscriber &subscriber)
{
    viewport.RemoveViewport2Subscriber(subscriber);
}

void UiElement::NotifyOnViewportSizeChanged(const Viewport2EventInfo &event)
{
    viewport.NotifyOnViewportSizeChanged(event);
}

void UiElement::NotifyOnViewportPositionChanged(const Viewport2EventInfo &event)
{
    viewport.NotifyOnViewportPositionChanged(event);
}

void UiElement::SetViewportSize(const glm::vec3 &input)
{
    viewport.SetViewportSize(input);
}

void UiElement::SetViewportPosition(const glm::vec3 &input)
{
    viewport.SetViewportPosition(input);
}

const glm::vec3 & UiElement::GetViewportSize()
{
    return viewport.GetViewportSize();
}

const glm::vec3 & UiElement::GetViewportPosition()
{
    return viewport.GetViewportPosition();
}

void UiElement::ResetViewport()
{
    viewport.ResetViewport();
}

bool UiElement::IsViewportSet() const
{
    return viewport.IsViewportSet();
}

void UiElement::NotifyOnViewportReset(const Viewport2EventInfo &event)
{
    viewport.NotifyOnViewportReset(event);
}
