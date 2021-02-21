#pragma once
#include "Renderable.h"
#include "DefaultRender.h"
#include <Windows.h>
#include <gdiplus.h>
#include "ClassMethod.h"
#include <unordered_map>
#include "Reflectable.h"
#include "ReflectionContainer.h"


class SimpleBorder : public Renderable, public Reflectable<SimpleBorder>
{
private:
	//Field map

	Gdiplus::SolidBrush* brush;
	Gdiplus::Pen* pen;
	DefaultRender renderBehavior;
	Gdiplus::Color color;

public:
	ReflectionContainer<SimpleBorder> reflectionContainer;
	SimpleBorder(); 
	~SimpleBorder();
	void SetColor(Gdiplus::Color color);
	Gdiplus::Color GetColor();
	void SetBorderStyle(Gdiplus::DashStyle style);
	void SetThickness(float thickness);

	// Inherited via Renderable
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;

	// Inherited via Reflectable
	virtual bool HasMethod(std::string method) override;

	// Inherited via Reflectable
	virtual ReflectionContainer<SimpleBorder>& GetReflectionContainer() override;
};

