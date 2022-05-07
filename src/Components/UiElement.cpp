#include "UiElement.h"
#include "Window.h"
#include "EventTypes/EventResizeInfo.h"
#include "EventTypes/RenderEventInfo.h"
#include "EventTypes/EventUpdateInfo.h"
#include "EventTypes/EventKeyStateInfo.h"
#include "DrawData2D.h"
#include <execution>
#include <future>
#include <algorithm>
#include "CoreWindow.h"

void UiElement::Add(std::unique_ptr<UiElement> uiElement)
{
    auto root = dynamic_cast<Window*>(&GetRoot());
    if(root != nullptr)
        root->WaitForSync();

    addToContainerMutex.lock();
    std::unique_ptr<MultiTree<std::unique_ptr<UiElement>>> nodeToBeAdded {&uiElement->GetUiElementNode()};
    uiElementNode->AddNode(std::move(nodeToBeAdded));
    //
    uiElement.release();
    addToContainerMutex.unlock();

    //RegisterComponent to the memory manager
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw)); //Recalculate offsets based on the current parent
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
	viewport(*this),
	keyStateBehavior(*this),
	resizeBehavior(*this)
{
	moveBehavior.SetPosition(x, y);
	resizeBehavior.SetSize(width, height);
	this->name = name;
}

std::wstring UiElement::GetText()
{
	return text;
}

void UiElement::SetText(std::wstring text)
{
	this->text = text;
	//Repaint();
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

void UiElement::NotifyOnMoveSubscribers(EventMoveInfo event)
{
	moveBehavior.NotifyOnMoveSubscribers(event);
}

void UiElement::SetX(float x)
{
    //Can't change during sync.
    //Perform a data update
    //Notify the root that the data was updated

	moveBehavior.SetX(x);

	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::SetY(float y)
{
	moveBehavior.SetY(y);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::OnRender(RenderEventInfo e)
{
	renderBehavior.OnRender(e);
}

void UiElement::OnSync(const DrawData &data)
{
    Vector2 parentPos = {0, 0};
    if( !IsRoot())
    {
        parentPos.SetX(GetX());
        parentPos.SetY(GetY());
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
	resizeBehavior.AddOnResizeSubscriber(subscriber);
}

void UiElement::RemoveOnResizeSubscriber(ResizeSubscriber& subscriber)
{
	resizeBehavior.RemoveOnResizeSubscriber(subscriber);
}

void UiElement::SetWidth(float width)
{
	resizeBehavior.SetWidth(width);
}

void UiElement::SetHeight(float height)
{
	resizeBehavior.SetHeight(height);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

std::vector<std::reference_wrapper<RenderCommander>> UiElement::GetRenderables()
{
	return renderBehavior.GetRenderables();
}

void UiElement::AddOnViewportMoveSubscriber(MoveSubscriber& subscriber)
{
	viewport.AddOnMoveSubscriber(subscriber);
}

void UiElement::RemoveOnViewportMoveSubscriber(MoveSubscriber& subscriber)
{
	viewport.RemoveOnMoveSubscriber(subscriber);
}

void UiElement::NotifyOnViewportMoveSubscribers(EventMoveInfo event)
{
	viewport.NotifyOnMoveSubscribers(event);
}

void UiElement::SetViewportXMultiplier(float x)
{
	viewport.SetXMultiplier(x);
}

void UiElement::SetViewportYMultiplier(float y)
{
	viewport.SetYMultiplier(y);
}

void UiElement::SetViewportWidthMultiplier(float width)
{
	viewport.SetWidthMultiplier(width);
}

void UiElement::SetViewportHeightMultiplier(float height)
{
	viewport.SetHeightMultiplier(height);
}

float UiElement::GetViewportXMultiplier()
{
	return viewport.GetViewportXMultiplier();
}

float UiElement::GetViewportYMultiplier()
{
	return viewport.GetViewportYMultiplier();
}

float UiElement::GetViewportWidthMultiplier()
{
	return viewport.GetViewportWidthMultiplier();
}

float UiElement::GetViewportHeightMultiplier()
{
	return viewport.GetViewportHeightMultiplier();
}

void UiElement::SetViewportXOffset(int x)
{
	viewport.SetX(x);
}

void UiElement::SetViewportYOffset(int y)
{
	viewport.SetY(y);
}

void UiElement::SetViewportOffset(Vector2 offset)
{
	viewport.SetPosition(offset);
}

int UiElement::GetViewportAbsoluteX()
{
	return viewport.GetAbsoluteX();
}

int UiElement::GetViewportAbsoluteY()
{
	return viewport.GetAbsoluteY();
}

Vector2 UiElement::GetViewportAbsolutePosition()
{
	return viewport.GetAbsolutePosition();
}

int UiElement::GetViewportX()
{
	return viewport.GetX();
}

int UiElement::GetViewportY()
{
	return viewport.GetY();
}

Vector2 UiElement::GetViewportPosition()
{
	return viewport.GetPosition();
}

void UiElement::NotifyOnViewportResizeSubscribers(EventResizeInfo event)
{
	viewport.NotifyOnResizeSubscribers(event);
}

void UiElement::AddOnViewportResizeSubscriber(ResizeSubscriber& subscriber)
{
	viewport.AddOnResizeSubscriber(subscriber);
}

void UiElement::RemoveOnViewportResizeSubscriber(ResizeSubscriber& subscriber)
{
	viewport.RemoveOnResizeSubscriber(subscriber);
}

int UiElement::GetViewportWidth()
{
	return viewport.GetWidth();
}

int UiElement::GetViewportHeight()
{
	return viewport.GetHeight();
}

void UiElement::SetViewportSize(Vector2 size)
{
	viewport.SetSize(size);
}

void UiElement::SetViewportSize(int width, int height)
{
	viewport.SetSize(width, height);
}

void UiElement::SetViewportWidth(int width)
{
	viewport.SetWidth(width);
}

void UiElement::SetViewportHeight(int height)
{
	viewport.SetHeight(height);
}

Vector2 UiElement::GetViewportSize()
{
	return viewport.GetSize();
}

int UiElement::GetViewportAbsoluteWidth()
{
	return viewport.GetViewportAbsoluteWidth();
}

int UiElement::GetViewportAbsoluteHeight()
{
	return viewport.GetViewportAbsoluteHeight();
}

Vector2 UiElement::GetViewportAbsoluteSize()
{
	return viewport.GetViewportAbsoluteSize();
}

void UiElement::OnUpdate(EventUpdateInfo e)
{
	moveBehavior.CalculateAbsolutePosition(); 
	viewport.OnUpdate(e);
	UpdateSubNodes(e); // Go through everything in the tree and update it, Only the first component in the tree should call redraw.
	if (!e.HasFlag(EventUpdateFlags::Redraw))
		return;
	//Repaint();
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
	mouseHandler.NotifyOnMouseDown(EventMouseStateInfo(e, this));
}

void UiElement::NotifyOnMouseUp(EventMouseStateInfo e)
{
	mouseHandler.NotifyOnMouseUp(EventMouseStateInfo(e, this));
}

void UiElement::NotifyOnMousePressed(EventMouseStateInfo e)
{
	mouseHandler.NotifyOnMousePressed(EventMouseStateInfo(e, this));
}

void UiElement::NotifyOnMouseHover(EventMouseStateInfo e)
{
	mouseHandler.NotifyOnMouseHover(EventMouseStateInfo(e, this));
}

void UiElement::AddMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	mouseHandler.AddMouseStateSubscriber(subscriber);
}

void UiElement::RemoveMouseStateSubscriber(MouseStateSubscriber& subscriber)
{
	mouseHandler.RemoveMouseStateSubscriber(subscriber);
}

bool UiElement::ColidesWithPoint(Vector2 point)
{
	if ( !(point.GetX() >= GetAbsoluteX() && point.GetX() <= GetAbsoluteX() + GetWidth()) )
		return false;
	if ( !(point.GetY() >= GetAbsoluteY() && point.GetY() <= GetAbsoluteY() + GetHeight()) )
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

std::any UiElement::ColidesWithUpmost(Vector2 point)
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

void UiElement::SetTranslate(Vector2 offset)
{
	if (ignoreTranslate)
		return;

    moveBehavior.SetTranslate(offset);
}

void UiElement::SetTranslateX(float x)
{
	if (ignoreTranslate)
		return;
    moveBehavior.SetTranslateX(x);
}

void UiElement::SetTranslateY(float y)
{
	if (ignoreTranslate)
		return;

    moveBehavior.SetTranslateY(y);
}

Vector2 UiElement::GetTranslate()
{
	return moveBehavior.GetTranslate();
}

float UiElement::GetTranslateX()
{
	return moveBehavior.GetTranslateX();
}

float UiElement::GetTranslateY()
{
	return moveBehavior.GetTranslateY();
}

Vector2 UiElement::GetChildrenTranslate()
{
	return moveBehavior.GetChildrenTranslate();
}

void UiElement::SetChildrenTranslate(Vector2 internalOffset)
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


float UiElement::GetAbsoluteX()
{
	return moveBehavior.GetAbsoluteX();
}

float UiElement::GetAbsoluteY()
{
	return moveBehavior.GetAbsoluteY();
}

Vector2 UiElement::GetAbsolutePosition()
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

Vector2 UiElement::GetSize()
{
	return resizeBehavior.GetSize();
}

Vector2 UiElement::GetPosition()
{
	return moveBehavior.GetPosition();
}

float UiElement::GetWidth()
{
	return resizeBehavior.GetWidth();
}

float UiElement::GetHeight()
{
	return resizeBehavior.GetHeight();
}

float UiElement::GetX()
{
	return moveBehavior.GetX();
}

MultiTree<std::unique_ptr<UiElement>> & UiElement::GetUiElementNode()
{
	return *uiElementNode;
}


float UiElement::GetY()
{
	return moveBehavior.GetY();
}

UiElement * UiElement::GetParent()
{
	if (uiElementNode->GetParent() == nullptr)
		return nullptr;
	return uiElementNode->GetParent().get();
}


void UiElement::SetSize(float width, float height)
{
    ///Wait for sync
	resizeBehavior.SetSize(width, height);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::SetSize(Vector2 size)
{
	resizeBehavior.SetSize(size);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::AddOnResizeListener(ResizeSubscriber& subscriber)
{
	resizeBehavior.AddOnResizeSubscriber(subscriber);
}

void UiElement::SetPosition(float x, float y)
{
	moveBehavior.SetPosition(x, y);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::SetPosition(Vector2 pos)
{
	moveBehavior.SetPosition(pos);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::NotifyOnMouseCapture(EventMouseStateInfo e)
{
    mouseHandler.NotifyOnMouseCapture(EventMouseStateInfo(e, this));
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

    std::for_each(std::execution::par, uiElementNode->GetNodes().begin(), uiElementNode->GetNodes().end(), [&](auto& node)
    {
        node->GetValue()->NotifyOnTick();
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
