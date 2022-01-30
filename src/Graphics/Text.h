#pragma once
#include "Renderable.h"
#include "DefaultRender.h"
#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include "Reflectable.h"
#include <unordered_map>
#include "ReflectionContainer.h"
#include "ScalingUtil.h"
#include "FontFormat.h"
#include "Vector4.h"
#include "Vector3.h"
#include "FontAlignment.h"

/**
 * A text renderable. Draws text within the canvas of the defined object.
 * Supported properties:<br>
 * text-color, args: Gdiplus::Color<br>
 * font-size, args: double
 */
class Text : public Renderable, public Reflectable<Text>
{
private:
	DefaultRender renderBehavior;
	std::wstring fontFamily;
	Vector2 position;
	Vector4 color;
	ScalingUtil graphicsUtil;

	ReflectionContainer<Text> reflectionContainer;
	float fontSize = 12.0f;
	std::wstring text;

	int lineAlignment = FontAlingnment::FontAlignmentNear;
	int alignment = FontAlingnment::FontAlignmentNear;

public:
	void SetLineAlignment(int alignment);
	void SetAlignment(int alignment);

	int GetLineAlignment();
	int GetAlignment();

	Text(std::string fontFamily);
	void SetText(std::wstring text);
	std::wstring GetText();
	virtual void SetColor(Vector3 color);
	virtual void SetFontSize(float fontSize);
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable &renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;



	GraphicsScaling GetScalingTypeX() const;
	void SetScalingTypeX(GraphicsScaling scalingTypeX);
	GraphicsScaling GetScalingTypeY() const;
	void SetScalingTypeY(GraphicsScaling scalingTypeY);

	Vector2 GetPosition();
	void SetPosition(Vector2 position);
	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();

	// Inherited via Reflectable
	virtual bool HasMethod(std::string method) override;

	// Inherited via Reflectable
	virtual ReflectionContainer<Text>& GetReflectionContainer() override;
};

