#pragma once
#include "Renderable.h"
#include <Windows.h>
#include <gdiplus.h>
#include "DefaultRender.h"
#include "ReflectionContainer.h"
/**
 * A background renderable. Displays a backround with the defined color in the entire canvas of the component.
 * Supported properties:
 * background-color, args: Gdiplus::Color, return void
 * get-background-color, return Gdiplus::Color
 */
class Background : public Renderable, public Reflectable<Background>
{
private:
	DefaultRender renderBehavior;
	Gdiplus::SolidBrush* brush;
	Gdiplus::Color currentColor;
	ReflectionContainer<Background> reflectionContainer;
	Gdiplus::PointF percentualPos;
	Gdiplus::PointF posOffset;

	Gdiplus::SizeF size;

public:
	Background();
	~Background();

	void SetColor(Gdiplus::Color color);
	Gdiplus::Color GetColor();
	void SetWidth(float width);
	void SetHeight(float height);
	void SetPercentualPosX(float x);
	void SetPercentualPosY(float y);

	float GetWidth();
	float GetHeight();
	float GetPercentualPosX();
	float GetPercentualPosY();

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

