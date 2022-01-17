#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "Components/Renderable.h"
#include "DefaultRender.h"
#include "GraphicsScaling.h"
#include "Graphics2dUtil.h"
class CircleBorder : public Renderable
{
protected:
	float diameter = 1;
	float thickness = 12;

    Graphics2dUtil graphicsUtil;

    Gdiplus::Pen* pen;
	Gdiplus::SolidBrush* brush;
	DefaultRender renderBehavior;

public:
	Gdiplus::PointF position;
	Gdiplus::SizeF size;

	CircleBorder();
	~CircleBorder();
	void SetDiameter(float diameter);
	void SetThickness(float thickness);
	void SetColor(Gdiplus::Color color);

	Gdiplus::PointF GetPosition();
	void SetPosition(Gdiplus::PointF point);
	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();
	
	float GetDiameter();
	float GetThickness();

	// Inherited via Renderable
	void OnRender(RenderEventInfo e) override;
	void Repaint() override;
	void AddRenderable(Renderable& renderable) override;
	void RemoveRenderable(Renderable& renderable) override;
	std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;



	GraphicsScaling GetScalingTypeX() const;
	void SetScalingTypeX(GraphicsScaling scalingTypeX);
	GraphicsScaling GetScalingTypeY() const;
	void SetScalingTypeY(GraphicsScaling scalingTypeY);
	GraphicsScaling GetScalingTypeWidth() const;
	void SetScalingTypeWidth(GraphicsScaling scalingTypeWidth);
	GraphicsScaling GetScalingTypeHeight() const;
	void SetScalingTypeHeight(GraphicsScaling scalingTypeHeight);

	bool IsDrawFromCenterY() const;
	void SetDrawFromCenterY(bool drawFromCenterY);
	bool IsDrawFromCenterX() const;
	void SetDrawFromCenterX(bool drawFromCenterX);
};

