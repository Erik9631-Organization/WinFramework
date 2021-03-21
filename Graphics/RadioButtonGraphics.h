#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "Renderable.h"
#include "DefaultRender.h"
#include "CircleBackground.h"
#include "CircleBorder.h"

class RadioButtonGraphics : public Renderable
{
private:
	DefaultRender renderBehavior;
	CircleBackground fill;
	CircleBorder border;
	bool fillEnabled = false;
	Gdiplus::Color fillBackground;
	float fillPadding = 0;

	void UpdateFill();

public:
	RadioButtonGraphics();
	void SetFillEnabled(bool state);
	void SetThickness(float thickness);
	void SetRadius(float radius);
	void SetPercentualPosition(Gdiplus::PointF percentualPos);
	void SetOffset(Gdiplus::PointF offset);
	void SetBorderColor(Gdiplus::Color borderColor);
	void SetFillColor(Gdiplus::Color color);
	void SetDrawFromCenter(bool state);
	void SetScalingType(int type);
	void SetFillPadding(float padding);
	float GetFillPadding();

	float GetRadius();
	Gdiplus::PointF GetPercentualPosition();
	Gdiplus::PointF GetOffset();

	// Inherited via Renderable
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;
};

