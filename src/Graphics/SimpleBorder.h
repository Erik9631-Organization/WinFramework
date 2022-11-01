#pragma once
#include "api/RenderCommander.h"
#include "DefaultRender.h"
#include <Windows.h>
#include <gdiplus.h>
#include "ClassMethod.h"
#include <unordered_map>
#include "Reflectable.h"
#include "ReflectionContainer.h"
#include "ScalingUtil.h"
#include "Vector4.h"
#include "DrawData2D.h"


/**
 * A border renderable. Draws a border around the edges of the target object.
 * Supported properties:<br>
 * border-color, args: Gdiplus::Color, return void<br>
 * border-style, args: Gdiplus::DashStyle<br>
 * border-thickness, args: float
 */

class SimpleBorder : public RenderCommander, public Reflectable<SimpleBorder>
{
private:
	//Field map
	DefaultRender renderBehavior;
	Vector4 color;

	ScalingUtil graphicsUtil;
	float thickness;
    glm::vec2 position;
    glm::vec2 size;
	DrawData2D drawData;

public:
	ReflectionContainer<SimpleBorder> reflectionContainer;
	SimpleBorder(); 
	~SimpleBorder();
	void SetColor(Vector3 color);
	void SetColor(Vector4 color);
	Vector3 GetColor();
	Vector4 GetColorRGBA();
	void SetThickness(float thickness);
	void DrawFromCenterY(bool state);
	void DrawFromCenterX(bool state);

	// Inherited via Renderable
	void OnRenderSync(RenderEventInfo e) override;
	void Repaint() override;
	void AddRenderCommander(RenderCommander &renderable) override;
	void RemoveRenderCommander(RenderCommander& renderable) override;
	std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;
	glm::vec2 GetSize();
	glm::vec2 GetPosition();
	void SetSize(const glm::vec2 &size);
	void SetPosition(const glm::vec2 &point);
	void SetX(float x);
	void SetY(float y);
	void SetWidth(float width);
	void SetHeight(float height);
	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();


	GraphicsScaling GetScalingTypeX() const;
	void SetScalingTypeX(GraphicsScaling scalingTypeX);
	GraphicsScaling GetScalingTypeY() const;
	void SetScalingTypeY(GraphicsScaling scalingTypeY);
	GraphicsScaling GetScalingTypeWidth() const;
	void SetScalingTypeWidth(GraphicsScaling scalingTypeWidth);
	GraphicsScaling GetScalingTypeHeight() const;
	void SetScalingTypeHeight(GraphicsScaling scalingTypeHeight);


	// Inherited via Reflectable
	bool HasMethod(std::string method) override;

	// Inherited via Reflectable
	ReflectionContainer<SimpleBorder>& GetReflectionContainer() override;
    void OnSync(const DrawData &data) override;
};

