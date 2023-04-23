#include "UiElement.h"
#include "Window.h"
#include "EventUpdateInfo.h"
#include "DrawData2D.h"
#include <execution>
#include <algorithm>
#include "WindowsCore.h"
using namespace std;

UiElement & UiElement::Add(std::unique_ptr<UiElement> uiElement)
{
    auto& elementRef = *uiElement.release();;
    auto root = dynamic_cast<Window*>(&GetRoot());
    //We always draw the added element on top of the current element(The parent)

    std::unique_ptr<MultiTree<std::unique_ptr<UiElement>>> nodeToBeAdded {&elementRef.GetUiElementNode()};
    uiElementNode->AddNode(std::move(nodeToBeAdded));

    if(root != nullptr)
        elementRef.NotifyOnMounted(static_cast<Presenter&>(*root));

    elementRef.SetZ(GetZ() - 1);


    //RegisterComponent to the memory manager
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw)); //Recalculate offsets based on the current parent

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
	viewport(*this),
	keyStateBehavior(*this),
	resizeBehavior(*this)
{
    moveBehavior.SetPosition(x, y, 0, 0, false);
    resizeBehavior.SetSize(width, height, false);
	this->name = name;
}

const wstring & UiElement::GetText()
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

void UiElement::SetX(float x, bool emit)
{
    //Can't change during sync.
    //Perform a data update
    //Notify the root that the data was updated

    moveBehavior.SetX(x, emit);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::SetY(float y, bool emit)
{
    moveBehavior.SetY(y, emit);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::OnRenderSync(RenderEventInfo e)
{
    renderBehavior.OnRenderSync(e);
}

void UiElement::OnSync(const DrawData &data)
{
    auto parentPos = glm::vec4(0, 0, 0, 1);

    if(!IsRoot())
    {
        parentPos.x = GetX();
        parentPos.y = GetY();
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

void UiElement::SetWidth(float width, bool emit)
{
    resizeBehavior.SetWidth(width, emit);
}

void UiElement::SetHeight(float height, bool emit)
{
    resizeBehavior.SetHeight(height, emit);
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
    viewport.SetX(x, false);
}

void UiElement::SetViewportYOffset(int y)
{
    viewport.SetY(y, false);
}

void UiElement::SetViewportOffset(glm::vec4 offset)
{
    viewport.SetPosition(offset, false);
}

int UiElement::GetViewportAbsoluteX()
{
	return viewport.GetAbsoluteX();
}

int UiElement::GetViewportAbsoluteY()
{
	return viewport.GetAbsoluteY();
}

glm::vec4 UiElement::GetViewportAbsolutePosition()
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

glm::vec4 UiElement::GetViewportPosition()
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

void UiElement::SetViewportSize(glm::vec4 size)
{
    viewport.SetSize(size, false);
}

void UiElement::SetViewportSize(int width, int height)
{
    viewport.SetSize(width, height, false);
}

void UiElement::SetViewportWidth(int width)
{
    viewport.SetWidth(width, false);
}

void UiElement::SetViewportHeight(int height)
{
    viewport.SetHeight(height, false);
}

glm::vec4 UiElement::GetViewportSize()
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

glm::vec4 UiElement::GetViewportAbsoluteSize()
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

bool UiElement::ColidesWithPoint(glm::vec4 point)
{
	if ( !(point.x >= GetAbsoluteX() && point.x <= GetAbsoluteX() + GetWidth()) )
		return false;
	if ( !(point.y >= GetAbsoluteY() && point.y <= GetAbsoluteY() + GetHeight()) )
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

std::any UiElement::ColidesWithUpmost(glm::vec4 point)
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

void UiElement::SetTranslate(glm::vec4 offset, bool emit)
{
	if (ignoreTranslate)
		return;

    moveBehavior.SetTranslate(offset, emit);
}

void UiElement::SetTranslateX(float x, bool emit)
{
	if (ignoreTranslate)
		return;
    moveBehavior.SetTranslateX(x, emit);
}

void UiElement::SetTranslateY(float y, bool emit)
{
	if (ignoreTranslate)
		return;

    moveBehavior.SetTranslateY(y, emit);
}

glm::vec4 UiElement::GetTranslate()
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

glm::vec4 UiElement::GetChildrenTranslate()
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


float UiElement::GetAbsoluteX()
{
	return moveBehavior.GetAbsoluteX();
}

float UiElement::GetAbsoluteY()
{
	return moveBehavior.GetAbsoluteY();
}

const glm::vec4 & UiElement::GetAbsolutePosition()
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

const glm::vec4 & UiElement::GetSize()
{
	return resizeBehavior.GetSize();
}

glm::vec4 UiElement::GetPosition()
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

MultiTree<std::unique_ptr<UiElement>> & UiElement::GetUiElementNode()
{
	return *uiElementNode;
}

float UiElement::GetX()
{
    return moveBehavior.GetX();
}

float UiElement::GetY()
{
	return moveBehavior.GetY();
}

float UiElement::GetZ() {
    return moveBehavior.GetZ();
}

float UiElement::GetW() {
    return moveBehavior.GetW();
}

UiElement * UiElement::GetParent()
{
	if (uiElementNode->GetParent() == nullptr)
		return nullptr;
	return uiElementNode->GetParent().get();
}


void UiElement::SetSize(float width, float height, bool emit)
{
    ///Wait for sync
    resizeBehavior.SetSize(width, height, emit);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::SetSize(const glm::vec4 &size, bool emit)
{
    resizeBehavior.SetSize(size, emit);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::AddOnResizeListener(ResizeSubscriber& subscriber)
{
	resizeBehavior.AddOnResizeSubscriber(subscriber);
}

void UiElement::SetPosition(float x, float y, float z, float w, bool emit)
{
    moveBehavior.SetPosition(x, y, z, w, emit);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void UiElement::SetPosition(glm::vec4 pos, bool emit)
{
    moveBehavior.SetPosition(pos, emit);
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

void UiElement::SetPosition(glm::vec4 position)
{
    SetPosition(position, true);
}

void UiElement::SetPosition(float x, float y, float z, float w)
{
    SetPosition(x, y, 0, 0, true);
}

void UiElement::SetX(float x)
{
    SetX(x, true);
}

void UiElement::SetY(float y)
{
    SetY(y, true);
}

void UiElement::SetZ(float z, bool emit)
{
    SetPosition(GetX(), GetY(), z, GetW(), emit);
}

void UiElement::SetZ(float z)
{
    SetZ(z, true);
}

void UiElement::SetW(float w, bool emit)
{
    SetPosition(GetX(), GetY(), GetZ(), w, emit);
}

void UiElement::SetW(float w)
{
    SetZ(w);
}

void UiElement::SetTranslate(glm::vec4 offset)
{
    SetTranslate(offset, true);
}

void UiElement::SetTranslateX(float x)
{
    SetTranslateX(x, true);
}

void UiElement::SetTranslateY(float y)
{
    SetTranslateY(y, true);
}

void UiElement::SetSize(glm::vec4 size)
{
    SetSize(size, true);
}

void UiElement::SetSize(float width, float height)
{
    SetSize(width, height, true);
}

void UiElement::SetWidth(float width)
{
    SetWidth(width, true);
}

void UiElement::SetHeight(float height)
{
    SetHeight(height, true);
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
