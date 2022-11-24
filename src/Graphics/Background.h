#pragma once
#include "api/RenderCommander.h"
#include "DefaultRender.h"
#include "ReflectionContainer.h"
#include "ScalingUtil.h"
#include "Vector3.h"
#include "Vector4.h"
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
	Vector4 currentColor;
	ReflectionContainer<Background> reflectionContainer;
    glm::vec2 position;
	ScalingUtil graphicsUtil;
    glm::vec2 size;
	DrawData2D drawData;

public:
	Background();
	~Background();

	void SetColor(Vector3 color);
	void SetColor(Vector4 color);
	Vector3 GetColor();
	Vector4 GetColorRGBA();
	void SetWidth(float width);
	void SetHeight(float height);
	void SetPosition(glm::vec2 position);
	void SetSize(glm::vec2 size);

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

	glm::vec2 GetSize();
	glm::vec2 GetPosition();

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

