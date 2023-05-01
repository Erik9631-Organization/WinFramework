#pragma once
#include "RenderCommander.h"
#include "DefaultRender.h"
#include "ClassMethod.h"
#include <unordered_map>
#include "Reflectable.h"
#include "ReflectionContainer.h"
#include "ScalingUtil2D.h"
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
	glm::ivec4 color;

	ScalingUtil2D graphicsUtil;
	float thickness;
    glm::vec4 position{0};
    glm::vec4 size{0};
	DrawData2D drawData;

public:
	ReflectionContainer<SimpleBorder> reflectionContainer;
	SimpleBorder(); 
	~SimpleBorder();
	void SetColor(glm::ivec3 color);
	void SetColor(glm::ivec4 color);
	glm::ivec3 GetColor();
	glm::ivec4 GetColorRGBA();
	void SetThickness(float thickness);
	void DrawFromCenterY(bool state);
	void DrawFromCenterX(bool state);

	// Inherited via Renderable
	void OnRenderSync(RenderEventInfo e) override;
	void Repaint() override;
	void AddRenderCommander(RenderCommander &renderable) override;
	void RemoveRenderCommander(RenderCommander& renderable) override;
	std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;
	glm::vec4 GetSize();
	glm::vec4 GetPosition();
	void SetSize(glm::vec4 size);
	void SetPosition(glm::vec4 point);
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

