#pragma once
#include "Events/MouseStateSubscriber.h"
#include <Windows.h>
#include <gdiplus.h>

class Button;
class DefaultButtonBehavior : public MouseStateSubscriber
{
private:
	Button& associatedButton;
	Gdiplus::Color standardColor;
	Gdiplus::Color onClickColor;
	Gdiplus::Color onHoverColor;
public:
	DefaultButtonBehavior(Button& button);
	void SetOnHoverColor(Gdiplus::Color color);
	void SetOnClickColor(Gdiplus::Color color);
	void SetStatelessColor(Color statelessColor);

	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;
	virtual void OnMouseUp(EventMouseStateInfo e) override;
	virtual void OnMousePressed(EventMouseStateInfo e) override;
	virtual void OnMouseMove(EventMouseStateInfo e) override;
	virtual void OnMouseEntered(EventMouseStateInfo e) override;
	virtual void OnMouseLeft(EventMouseStateInfo e) override;
    void OnMouseCaptured(EventMouseStateInfo e) override;

    Color GetStandardColor();
    Color GetOnClickColor();
    Color GetOnHoverColor();

};

