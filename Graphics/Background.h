#pragma once
#include "Renderable.h"
#include <Windows.h>
#include <gdiplus.h>
#include "DefaultRender.h"

class Background : public Renderable
{
private:
	DefaultRender renderBehavior;
	Gdiplus::SolidBrush* brush;
public:
	Background();
	~Background();

	void SetColor(Gdiplus::Color color);

	// Inherited via Renderable
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;
};

