#pragma once
#include "api/RenderCommander.h"
#include "DefaultRender.h"
#include "ReflectionContainer.h"
#include "ScalingUtil2D.h"
#include "DrawData2D.h"

/**
 * A background renderable. Displays a backround with the defined color in the entire canvas of the component.
 * Supported properties:
 * background-color, args: Gdiplus::Color, return void
 * get-background-color, return Gdiplus::Color
 */
class Background : public RenderCommander, public Reflectable<Background>
{
private:
	DefaultRender renderBehavior;
	glm::vec4 currentColor;
	ReflectionContainer<Background> reflectionContainer;
    glm::vec4 position;
	ScalingUtil2D graphicsUtil;
    glm::vec4 size;
	DrawData2D drawData;

public:
	Background();
	~Background();

	void SetColor(glm::vec3 color);
	void SetColor(glm::vec4 color);
	glm::vec3 GetColor();
	glm::vec3 GetColorRGBA();
	void SetWidth(float width);
	void SetHeight(float height);
	void SetPosition(glm::vec4 position);
	void SetSize(glm::vec4 size);

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

	glm::vec4 GetSize();
	glm::vec4 GetPosition();

	// Inherited via Renderable
	virtual void OnRenderSync(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderCommander(RenderCommander &renderable) override;
	virtual void RemoveRenderCommander(RenderCommander& renderable) override;
	virtual std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;

	// Inherited via Reflectable
	virtual bool HasMethod(std::string method) override;
	virtual ReflectionContainer<Background>& GetReflectionContainer();
    void OnSync(const DrawData &data) override;
};
