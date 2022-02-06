#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "Components/Renderable.h"
#include "DefaultRender.h"
#include "GraphicsScaling.h"
#include "ScalingUtil.h"
#include "Vector3.h"
#include "Vector4.h"
#include "DrawData2D.h"

class CircleBorder : public Renderable
{
protected:
	float diameter = 1;
	float thickness = 12;

    ScalingUtil graphicsUtil;
	DefaultRender renderBehavior;
	Vector4 color;
	DrawData2D drawData;

public:
	Vector2 position;
	Vector2 size;

	CircleBorder();
	~CircleBorder();
	void SetDiameter(float diameter);
	void SetThickness(float thickness);
	void SetColor(Vector3 color);
	void SetColor(Vector4 color);

	Vector2 GetPosition();
	void SetPosition(Vector2 point);
	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();
	
	float GetDiameter();
	float GetThickness();

	// Inherited via Renderable
	void OnRender(RenderEventInfo e) override;
	void Repaint() override;
	void AddRenderable(Renderable &renderable) override;
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
    void OnSync(const DrawData &data) override;
};

