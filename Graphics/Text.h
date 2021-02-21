#pragma once
#include "Renderable.h"
#include "DefaultRender.h"
#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include "Reflectable.h"
#include <unordered_map>
#include "ReflectionContainer.h"

class Text : public Renderable, public Reflectable<Text>
{
private:
	DefaultRender renderBehavior;
	Gdiplus::FontFamily* fontFamily;
	Gdiplus::Font* font;
	Gdiplus::PointF position;
	Gdiplus::SolidBrush* brush;
	ReflectionContainer<Text> reflectionContainer;
	float fontSize = 12.0f;
	std::wstring text;

public:
	// Inherited via Renderable
	Text(std::string fontFamily);
	void SetText(std::wstring text);
	std::wstring GetText();
	void SetPosition(Gdiplus::PointF position);
	Gdiplus::PointF GetPosition();
	virtual void SetColor(Gdiplus::Color);
	virtual void SetFontSize(double fontSize);
	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;

	// Inherited via Reflectable
	virtual bool HasMethod(std::string method) override;

	// Inherited via Reflectable
	virtual ReflectionContainer<Text>& GetReflectionContainer() override;
};

