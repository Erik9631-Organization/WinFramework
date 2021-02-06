#include "Component.h"
#include "WindowFrame.h"
#include "CoreWindowFrame.h"
#include "EventMoveInfo.h"
#include "ComponentListener.h"
#include "EventResizeInfo.h"
#include "RenderEventInfo.h"
#include "EventUpdateInfo.h"

void Component::Add(Component& component)
{
	componentNode.Add(component.GetComponentNode());
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw)); //Recalculate offsets based on the current parent
}



Component::Component() : Component(0, 0, 0, 0, "")
{

}

Component::Component(string name) : Component(0, 0, 0, 0, name)
{
}

Component::Component(int x, int y, int width, int height, string name) : componentNode(*this), moveBehavior((MultiTree<Adjustable&>&)componentNode), renderBehavior(*this), viewport(*this)
{
	moveBehavior.SetPosition(x, y);
	resizeBehavior.SetSize(width, height);
	this->name = name;
}

void Component::AddOnMoveSubscriber(MoveSubscriber& subscriber)
{
	moveBehavior.AddOnMoveSubscriber(subscriber);
}

void Component::RemoveOnMoveSubscriber(MoveSubscriber& subscriber)
{
	moveBehavior.RemoveOnMoveSubscriber(subscriber);
}

void Component::NotifyOnMoveSubscribers(EventMoveInfo event)
{
	moveBehavior.NotifyOnMoveSubscribers(event);
}

void Component::SetX(int x)
{
	moveBehavior.SetX(x);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void Component::SetY(int y)
{
	moveBehavior.SetY(y);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void Component::OnRender(RenderEventInfo e)
{
	Gdiplus::Matrix* matrix = new Gdiplus::Matrix();
	if( !IsRoot() ) //Root should always translate from 0, 0
		matrix->Translate(GetAbsoluteX(), GetAbsoluteY());
	matrix->Scale(GetWidth(), GetHeight());

	e.GetGraphics()->SetTransform(matrix);
	renderBehavior.OnRender(e);
	delete matrix;
}

void Component::Repaint()
{
	if (IsRoot())
		return;
	GetRoot().Repaint();
}

void Component::AddRenderable(Renderable& renderable)
{
	renderBehavior.AddRenderable(renderable);
}

void Component::RemoveRenderable(Renderable& renderable)
{
	renderBehavior.RemoveRenderable(renderable);
}

void Component::NotifyOnResizeSubscribers(EventResizeInfo event)
{
	resizeBehavior.NotifyOnResizeSubscribers(event);
}

void Component::AddOnResizeSubscriber(ResizeSubscriber& subscriber)
{
	resizeBehavior.AddOnResizeSubscriber(subscriber);
}

void Component::RemoveOnResizeSubscriber(ResizeSubscriber& subscriber)
{
	resizeBehavior.RemoveOnResizeSubscriber(subscriber);
}

void Component::SetWidth(int width)
{
	resizeBehavior.SetWidth(width);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void Component::SetHeight(int height)
{
	resizeBehavior.SetHeight(height);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

std::vector<std::reference_wrapper<Renderable>> Component::GetRenderables()
{
	return renderBehavior.GetRenderables();
}

void Component::AddOnViewportMoveSubscriber(MoveSubscriber& subscriber)
{
	viewport.AddOnMoveSubscriber(subscriber);
}

void Component::RemoveOnViewportMoveSubscriber(MoveSubscriber& subscriber)
{
	viewport.RemoveOnMoveSubscriber(subscriber);
}

void Component::NotifyOnViewportMoveSubscribers(EventMoveInfo event)
{
	viewport.NotifyOnMoveSubscribers(event);
}

void Component::SetViewportXMultiplier(float x)
{
	viewport.SetXMultiplier(x);
}

void Component::SetViewportYMultiplier(float y)
{
	viewport.SetYMultiplier(y);
}

void Component::SetViewportWidthMultiplier(float width)
{
	viewport.SetWidthMultiplier(width);
}

void Component::SetViewportHeightMultiplier(float height)
{
	viewport.SetHeightMultiplier(height);
}

float Component::GetViewportXMultiplier()
{
	return viewport.GetViewportXMultiplier();
}

float Component::GetViewportYMultiplier()
{
	return viewport.GetViewportYMultiplier();
}

float Component::GetViewportWidthMultiplier()
{
	return viewport.GetViewportWidthMultiplier();
}

float Component::GetViewportHeightMultiplier()
{
	return viewport.GetViewportHeightMultiplier();
}

void Component::SetViewportXOffset(int x)
{
	viewport.SetX(x);
}

void Component::SetViewportYOffset(int y)
{
	viewport.SetY(y);
}

void Component::SetViewportOffset(Gdiplus::Point offset)
{
	viewport.SetPosition(offset);
}

int Component::GetViewportAbsoluteX()
{
	return viewport.GetAbsoluteX();
}

int Component::GetViewportAbsoluteY()
{
	return viewport.GetAbsoluteY();
}

Gdiplus::Point Component::GetViewportAbsolutePosition()
{
	return viewport.GetAbsolutePosition();
}

int Component::GetViewportX()
{
	return viewport.GetX();
}

int Component::GetViewportY()
{
	return viewport.GetY();
}

Gdiplus::Point Component::GetViewportPosition()
{
	return viewport.GetPosition();
}

void Component::NotifyOnViewportResizeSubscribers(EventResizeInfo event)
{
	viewport.NotifyOnResizeSubscribers(event);
}

void Component::AddOnViewportResizeSubscriber(ResizeSubscriber& subscriber)
{
	viewport.AddOnResizeSubscriber(subscriber);
}

void Component::RemoveOnViewportResizeSubscriber(ResizeSubscriber& subscriber)
{
	viewport.RemoveOnResizeSubscriber(subscriber);
}

int Component::GetViewportWidth()
{
	return viewport.GetWidth();
}

int Component::GetViewportHeight()
{
	return viewport.GetHeight();
}

void Component::SetViewportSize(Gdiplus::Size size)
{
	viewport.SetSize(size);
}

void Component::SetViewportSize(int width, int height)
{
	viewport.SetSize(width, height);
}

void Component::SetViewportWidth(int width)
{
	viewport.SetWidth(width);
}

void Component::SetViewportHeight(int height)
{
	viewport.SetHeight(height);
}

Gdiplus::Size Component::GetViewportSize()
{
	return viewport.GetSize();
}

int Component::GetViewportAbsoluteWidth()
{
	return viewport.GetViewportAbsoluteWidth();
}

int Component::GetViewportAbsoluteHeight()
{
	return viewport.GetViewportAbsoluteHeight();
}

Gdiplus::Size Component::GetViewportAbsoluteSize()
{
	return viewport.GetViewportAbsoluteSize();
}

void Component::OnUpdate(EventUpdateInfo e)
{
	moveBehavior.CalculateAbsolutePosition(); 
	viewport.OnUpdate(e);
	UpdateSubNodes(e); // Go through everything in the tree and update it, Only the first component in the tree should call update.
	if (!e.HasFlag(EventUpdateFlags::Redraw))
		return;
	CoreWindowFrame::ConsoleWrite(name + " Sending repaint request...");
	Repaint();
}

void Component::UpdateSubNodes(EventUpdateInfo e)
{
	e.DisableFlag(EventUpdateFlags::Redraw); //Only the top of the subTree should do redraw
	for (int i = 0; i < componentNode.GetNodeCount(); i++)
	{
		MultiTree<Component&>& node = (MultiTree<Component&>&) componentNode.Get(i);
		node.GetValue().OnUpdate(EventUpdateInfo(e));
	}
}

int Component::GetAbsoluteX()
{
	return moveBehavior.GetAbsoluteX();
}

int Component::GetAbsoluteY()
{
	return moveBehavior.GetAbsoluteY();
}

Gdiplus::Point Component::GetAbsolutePosition()
{
	return moveBehavior.GetAbsolutePosition();
}

bool Component::IsRoot()
{
	return componentNode.IsRoot();
}

Component& Component::GetRoot()
{
	return componentNode.GetRoot().GetValue();
}

string Component::GetComponentType()
{
	return componentType;
}

string Component::GetComponentName()
{
	return name;
}

void Component::SetComponentName(string name)
{
	this->name = name;
}

Size Component::GetSize()
{
	return resizeBehavior.GetSize();
}

Point Component::GetPosition()
{
	return moveBehavior.GetPosition();
}

int Component::GetWidth()
{
	return resizeBehavior.GetWidth();
}

int Component::GetHeight()
{
	return resizeBehavior.GetHeight();
}

int Component::GetX()
{
	return moveBehavior.GetX();
}

DefaultMultiTree<Component&>& Component::GetComponentNode()
{
	return componentNode;
}

int Component::GetY()
{
	return moveBehavior.GetY();
}

Component * Component::GetParent()
{
	if (componentNode.GetParent() == nullptr)
		return nullptr;
	return (Component*)&componentNode.GetParent()->GetValue();
}

void Component::SetSize(int width, int height)
{
	resizeBehavior.SetSize(width, height);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void Component::SetSize(Size size)
{
	resizeBehavior.SetSize(size);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void Component::AddOnResizeListener(ResizeSubscriber& subscriber)
{
	resizeBehavior.AddOnResizeSubscriber(subscriber);
}

void Component::SetPosition(int x, int y)
{
	moveBehavior.SetPosition(x, y);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}

void Component::SetPosition(Point pos)
{
	moveBehavior.SetPosition(pos);
	OnUpdate(EventUpdateInfo(EventUpdateFlags::Redraw | EventUpdateFlags::Move));
}