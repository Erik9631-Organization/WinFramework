#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include "api/RenderCommander.h"
#include "DefaultRender.h"
#include "CircleBackground.h"
#include "CircleBorder.h"

class RadioButtonGraphics : public RenderCommander
{
private:
	DefaultRender renderBehavior;
	CircleBackground fill;
	CircleBorder border;
	bool fillEnabled = false;
	Vector4 fillBackground;
	float fillPadding = 0;
	void UpdateFill();

public:
	RadioButtonGraphics();
	void SetFillEnabled(bool state);
	void SetThickness(float thickness);
	void SetBorderColor(Vector3 borderColor);
	void SetFillColor(Vector3 color);

	void SetBorderColor(Vector4 borderColor);
	void SetFillColor(Vector4 color);

	void SetDiameter(float Diameter);
	float GetFillPadding();
	void SetFillPadding(float padding);

	void SetPosition(Vector2 position);
	Vector2 GetPosition();
	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();

	float GetDiameter();

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

	// Inherited via Renderable
	void OnRenderSync(RenderEventInfo e) override;
	void Repaint() override;
	void AddRenderCommander(RenderCommander &renderable) override;
	void RemoveRenderCommander(RenderCommander& renderable) override;
	std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;
    void OnSync(const DrawData &data) override;
};

