#pragma once
#include "api/RenderCommander.h"
#include "DefaultRender.h"
#include <string>
#include "Reflectable.h"
#include <unordered_map>
#include "ReflectionContainer.h"
#include "ScalingUtil2D.h"
#include "FontFormat.h"
#include "FontAlignment.h"
#include "DrawData2D.h"

/**
 * A text renderable. Draws text within the canvas of the defined object.
 * Supported properties:<br>
 * text-color, args: Gdiplus::Color<br>
 * font-viewPortPosition, args: double
 */
class Text : public RenderCommander, public Reflectable<Text>
{
private:
	DefaultRender renderBehavior;
	std::wstring fontFamily;
    glm::vec4 position;
	glm::ivec4 color;
	ScalingUtil2D graphicsUtil;
	ReflectionContainer<Text> reflectionContainer;
	float fontSize = 12.0f;
	std::wstring text;

	int lineAlignment = FontAlignment::FontAlignmentNear;
	int alignment = FontAlignment::FontAlignmentNear;

	DrawData2D drawData;

public:
	void SetLineAlignment(int alignment);
	void SetAlignment(int alignment);

	int GetLineAlignment();
	int GetAlignment();

	Text(std::string fontFamily);
	void SetText(std::wstring text);
	std::wstring GetText();
	virtual void SetColor(glm::ivec3 color);
	virtual void SetFontSize(float fontSize);
	virtual void OnRenderSync(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderCommander(RenderCommander &renderable) override;
	virtual void RemoveRenderCommander(RenderCommander& renderable) override;
	virtual std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;



	GraphicsScaling GetScalingTypeX() const;
	void SetScalingTypeX(GraphicsScaling scalingTypeX);
	GraphicsScaling GetScalingTypeY() const;
	void SetScalingTypeY(GraphicsScaling scalingTypeY);

	glm::vec4 GetPosition();
	void SetPosition(glm::vec4 position);
	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();

	// Inherited via Reflectable
	virtual bool HasMethod(std::string method) override;

	// Inherited via Reflectable
	virtual ReflectionContainer<Text>& GetReflectionContainer() override;
    void OnSync(const DrawData &data) override;
};

