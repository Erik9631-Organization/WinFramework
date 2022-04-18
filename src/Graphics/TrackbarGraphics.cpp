#include "TrackbarGraphics.h"
#include "EventTypes/RenderEventInfo.h"

TrackbarGraphics::TrackbarGraphics() : renderBehavior(*this), reflectionContainer(*this)
{
    reflectionContainer.RegisterMethod("tracker-color", "SetTrackerColor", &TrackbarGraphics::SetTrackerColor);
    reflectionContainer.RegisterMethod("tracker-position", "SetPercentualPosition", &TrackbarGraphics::SetPercentualPosition);
    reflectionContainer.RegisterMethod("tracker-height", "SetPercentualHeight", &TrackbarGraphics::SetPercentualHeight);

    reflectionContainer.RegisterMethod("get-tracker-height", "GetPercentualHeight", &TrackbarGraphics::GetPercentualHeight);
    reflectionContainer.RegisterMethod("get-tracker-position", "GetX", &TrackbarGraphics::GetPercentualPosition);

    reflectionContainer.RegisterMethod("get-tracker-color", "GetTrackerColor", &TrackbarGraphics::GetTrackerColor);

    border.SetColor({0, 0, 0});
    tracker.SetColor({0, 0, 0});

    AddRenderCommander(tracker);
    AddRenderCommander(border);
}

void TrackbarGraphics::SetPercentualHeight(float height)
{
    tracker.SetHeight(height);
    //Repaint();
}

float TrackbarGraphics::GetPercentualHeight()
{
    return tracker.GetHeight();
}

void TrackbarGraphics::SetPercentualPosition(float posY)
{
    tracker.SetY(posY);
    //Repaint();
}

float TrackbarGraphics::GetPercentualPosition()
{
    return tracker.GetY();
}

void TrackbarGraphics::SetTrackerColor(Vector3 color)
{
    tracker.SetColor(color);
}

Vector3 TrackbarGraphics::GetTrackerColor()
{
    return tracker.GetColor();
}

void TrackbarGraphics::OnRender(RenderEventInfo e)
{
    renderBehavior.OnRender(e);
}

void TrackbarGraphics::Repaint()
{
}

void TrackbarGraphics::AddRenderCommander(RenderCommander &renderable)
{
    renderBehavior.AddRenderCommander(renderable);
}

void TrackbarGraphics::RemoveRenderCommander(RenderCommander& renderable)
{
    renderBehavior.RemoveRenderCommander(renderable);
}

std::vector<std::reference_wrapper<RenderCommander>> TrackbarGraphics::GetRenderables()
{
    return renderBehavior.GetRenderables();
}

bool TrackbarGraphics::HasMethod(std::string method)
{
    return reflectionContainer.HasMethod(method);
}

ReflectionContainer<TrackbarGraphics>& TrackbarGraphics::GetReflectionContainer()
{
    return reflectionContainer;
}

void TrackbarGraphics::OnSync(const DrawData &data)
{
    renderBehavior.OnSync(data);
}
