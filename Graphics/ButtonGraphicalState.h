#pragma once
#include "MouseStateSubscriber.h"
#include <Windows.h>
#include <gdiplus.h>

class Button;
class ButtonGraphicalState : MouseStateSubscriber
{
private:
	Button& associatedButton;
	Gdiplus::Color onClickColor;
	Gdiplus::Color onHoverColor;

	Gdiplus::Color previousOnClickColor;
	Gdiplus::Color previousOnHoverColor;
public:
	ButtonGraphicalState(Button& button);
	void SetOnHoverColor(Gdiplus::Color color);
	void SetOnClickColor(Gdiplus::Color color);
	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;
	virtual void OnMouseUp(EventMouseStateInfo e) override;
	virtual void OnMousePressed(EventMouseStateInfo e) override;
	virtual void OnMouseMove(EventMouseStateInfo e) override;
	virtual void OnMouseEntered(EventMouseStateInfo e) override;
	virtual void OnMouseLeft(EventMouseStateInfo e) override;
};

