#pragma once
#include "Renderable.h"
#include "DefaultRender.h"
#include <Windows.h>
#include <gdiplus.h>
#include "ClassMethod.h"
#include <unordered_map>
#include "Reflectable.h"
#include "ReflectionContainer.h"
/**
 * A border renderable. Draws a border around the edges of the target object.
 * Supported properties:<br>
 * border-color, args: Gdiplus::Color, return void<br>
 * border-style, args: Gdiplus::DashStyle<br>
 * border-thickness, args: float
 */

class SimpleBorder : public Renderable, public Reflectable<SimpleBorder>
{
private:
	//Field map

	Gdiplus::SolidBrush* brush;
	Gdiplus::Pen* pen;
	DefaultRender renderBehavior;
	Gdiplus::Color color;

	Gdiplus::PointF offset;
	Gdiplus::SizeF size;
	int scalingType = 0;
	bool verticalCentering = false;
	bool horizontalCentering = false;
	bool textCentering = false;

public:
	ReflectionContainer<SimpleBorder> reflectionContainer;
	SimpleBorder(); 
	~SimpleBorder();
	void SetColor(Gdiplus::Color color);
	Gdiplus::Color GetColor();
	void SetBorderStyle(Gdiplus::DashStyle style);
	void SetThickness(float thickness);
	void SetScalingType(int type);
	void SetVerticalCentering(bool state);
	void HorizontalCentering(bool state);

	// Inherited via Renderable
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;
	Gdiplus::SizeF& GetSize();
	Gdiplus::PointF& GetPercentualPosition();

	// Inherited via Reflectable
	virtual bool HasMethod(std::string method) override;

	// Inherited via Reflectable
	virtual ReflectionContainer<SimpleBorder>& GetReflectionContainer() override;
};

