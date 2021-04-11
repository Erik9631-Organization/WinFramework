#pragma once
#include "Renderable.h"
#include "DefaultRender.h"
#include "SimpleBorder.h"
#include "Background.h"
#include "Reflectable.h"
#include "ReflectionContainer.h"

class Component;

class TrackbarGraphics : public Renderable, public Reflectable<TrackbarGraphics>
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
	void SetTrackerColor(Gdiplus::Color color);
	Gdiplus::Color GetTrackerColor();

	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;

	// Inherited via Reflectable
	virtual bool HasMethod(std::string method) override;
	virtual ReflectionContainer<TrackbarGraphics>& GetReflectionContainer();
};

