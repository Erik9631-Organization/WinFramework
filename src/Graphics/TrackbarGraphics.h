#pragma once
#include "api/RenderCommander.h"
#include "DefaultRender.h"
#include "Graphics/SimpleBorder.h"
#include "Graphics/Background.h"
#include "Components/Reflectable.h"
#include "Components/ReflectionContainer.h"
#include "DrawData2D.h"

class UiElement;

class TrackbarGraphics : public RenderCommander, public Reflectable<TrackbarGraphics>
{
private:
	DefaultRender renderBehavior;
	SimpleBorder border;
	Background tracker;
	ReflectionContainer<TrackbarGraphics> reflectionContainer;


public:
	// Inherited via Renderable
	TrackbarGraphics();

	void SetPercentualHeight(float height);
	float GetPercentualHeight();
	void SetPercentualPosition(float posY);
	float GetPercentualPosition();
	void SetTrackerColor(Vector3 color);
	Vector3 GetTrackerColor();

	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(RenderCommander &renderable) override;
	virtual void RemoveRenderable(RenderCommander& renderable) override;
	virtual std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;

	// Inherited via Reflectable
	virtual bool HasMethod(std::string method) override;
	virtual ReflectionContainer<TrackbarGraphics>& GetReflectionContainer();
    void OnSync(const DrawData &data) override;
};

