#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "api/RenderCommander.h"
#include "DefaultRender.h"
#include "GraphicsScaling.h"
#include "ScalingUtil.h"
#include "Vector3.h"
#include "Vector4.h"
#include "DrawData2D.h"

class CircleBorder : public RenderCommander
{
protected:
	float diameter = 1;
	float thickness = 12;

    ScalingUtil graphicsUtil;
	DefaultRender renderBehavior;
	Vector4 color;
	DrawData2D drawData;

public:
    glm::vec2 position{0};
    glm::vec2 size{0};

	CircleBorder();
	~CircleBorder();
	void SetDiameter(float diameter);
	void SetThickness(float thickness);
	void SetColor(Vector3 color);
	void SetColor(Vector4 color);

	glm::vec2 GetPosition();
	void SetPosition(const glm::vec2 &point);
	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();
	
	float GetDiameter();
	float GetThickness();

	// Inherited via Renderable
	void OnRenderSync(RenderEventInfo e) override;
	void Repaint() override;
	void AddRenderCommander(RenderCommander &renderable) override;
	void RemoveRenderCommander(RenderCommander& renderable) override;
	std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;



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

