#pragma once
#include "Renderable.h"
#include <Windows.h>
#include <gdiplus.h>
#include "DefaultRender.h"
#include "ReflectionContainer.h"

class Background : public Renderable, public Reflectable<Background>
{
private:
	DefaultRender renderBehavior;
	Gdiplus::SolidBrush* brush;
	Gdiplus::Color currentColor;
	ReflectionContainer<Background> reflectionContainer;

public:
	Background();
	~Background();

	void SetColor(Gdiplus::Color color);
	Gdiplus::Color GetColor();

	// Inherited via Renderable
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;

	// Inherited via Reflectable
	virtual bool HasMethod(std::string method) override;
	virtual ReflectionContainer<Background>& GetReflectionContainer();
};

