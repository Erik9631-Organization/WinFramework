#pragma once
#include "Components/Renderable.h"
#include <Windows.h>
#include <gdiplus.h>
#include "DefaultRender.h"
#include "ReflectionContainer.h"
#include "Graphics2dUtil.h"
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
	Gdiplus::PointF position;
	Gdiplus::PointF posOffset;
	Graphics2dUtil graphicsUtil;

	Gdiplus::SizeF size;

public:
	Background();
	~Background();

	void SetColor(Gdiplus::Color color);
	Gdiplus::Color GetColor();
	void SetWidth(float width);
	void SetHeight(float height);
	void SetPosition(Gdiplus::PointF position);
	void SetSize(Gdiplus::SizeF size);

	GraphicsScaling GetScalingTypeX() const;
	void SetScalingTypeX(GraphicsScaling scalingTypeX);
	GraphicsScaling GetScalingTypeY() const;
	void SetScalingTypeY(GraphicsScaling scalingTypeY);
	GraphicsScaling GetScalingTypeWidth() const;
	void SetScalingTypeWidth(GraphicsScaling scalingTypeWidth);
	GraphicsScaling GetScalingTypeHeight() const;
	void SetScalingTypeHeight(GraphicsScaling scalingTypeHeight);

	void SetX(float x);
	void SetY(float y);

	float GetWidth();
	float GetHeight();
	float GetX();
	float GetY();

	Gdiplus::SizeF GetSize();
	Gdiplus::PointF GetPosition();

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

