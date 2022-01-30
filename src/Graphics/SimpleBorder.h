#pragma once
#include "Components/Renderable.h"
#include "DefaultRender.h"
#include <Windows.h>
#include <gdiplus.h>
#include "ClassMethod.h"
#include <unordered_map>
#include "Reflectable.h"
#include "ReflectionContainer.h"
#include "ScalingUtil.h"
#include "Vector4.h"


/**
 * A border renderable. Draws a border around the edges of the target object.
 * Supported properties:<br>
 * border-color, args: Gdiplus::Color, return void<br>
 * border-style, args: Gdiplus::DashStyle<br>
 * border-thickness, args: float
 */

class SimpleBorder : public Renderable, public Reflectable<SimpleBorder>
{
private:
	//Field map
	DefaultRender renderBehavior;
	Vector4 color;

	ScalingUtil graphicsUtil;
	float thickness;


	Vector2 position;
	Vector2 size;
	GraphicsScaling scalingType = Percentual;

	GraphicsScaling scalingTypeX = Percentual;
	GraphicsScaling scalingTypeY = Percentual;
	GraphicsScaling scalingTypeWidth = Percentual;
	GraphicsScaling scalingTypeHeight = Percentual;

	bool drawFromCenterY = false;
	bool drawFromCenterX = false;
	bool textCentering = false;

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
	void OnRender(RenderEventInfo e) override;
	void Repaint() override;
	void AddRenderable(Renderable &renderable) override;
	void RemoveRenderable(Renderable& renderable) override;
	std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;
	Vector2 GetSize();
	Vector2 GetPosition();
	void SetSize(Vector2 size);
	void SetPosition(Vector2 point);
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
};

