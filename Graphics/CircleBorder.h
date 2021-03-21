#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "Renderable.h"
#include "DefaultRender.h"
class CircleBorder : public Renderable
{
protected:
	float diameter = 1;
	float thickness = 12;
	bool drawFromCenter = false;
	Gdiplus::Pen* pen;
	Gdiplus::SolidBrush* brush;
	int scalingType = 0;
	DefaultRender renderBehavior;

public:
	Gdiplus::PointF offset;
	Gdiplus::PointF percentualPosition;
	CircleBorder();
	~CircleBorder();
	void SetRadius(float radius);
	void SetThickness(float thickness);
	void SetDrawFromCenter(bool state);
	void SetScalingType(int scalingType);
	void SetColor(Gdiplus::Color color);
	
	float GetRadius();
	float GetThickness();

	// Inherited via Renderable
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;
};

