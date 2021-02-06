#pragma once
#include "Renderable.h"
#include "DefaultRender.h"
#include <Windows.h>
#include <gdiplus.h>


class SimpleBorder : public Renderable
{
private:
	Gdiplus::SolidBrush* brush;
	Gdiplus::Pen* pen;
	DefaultRender renderBehavior;
public:
	SimpleBorder(); 
	~SimpleBorder();
	void SetColor(Gdiplus::Color color);
	void SetBorderStyle(Gdiplus::DashStyle style);
	void SetThickness(float thickness);

	// Inherited via Renderable
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;
};

