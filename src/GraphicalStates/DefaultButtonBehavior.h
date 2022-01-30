#pragma once
#include "Events/MouseStateSubscriber.h"
#include <Windows.h>
#include <gdiplus.h>

class Button;
class DefaultButtonBehavior : public MouseStateSubscriber
{
private:
	Button& associatedButton;
	Vector3 standardColor;
	Vector3  onClickColor;
	Vector3  onHoverColor;
public:
	DefaultButtonBehavior(Button& button);
	void SetOnHoverColor(Vector3 color);
	void SetOnClickColor(Vector3 color);
	void SetStatelessColor(Vector3 statelessColor);

	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;
	virtual void OnMouseUp(EventMouseStateInfo e) override;
	virtual void OnMousePressed(EventMouseStateInfo e) override;
	virtual void OnMouseMove(EventMouseStateInfo e) override;
	virtual void OnMouseEntered(EventMouseStateInfo e) override;
	virtual void OnMouseLeft(EventMouseStateInfo e) override;
    void OnMouseCaptured(EventMouseStateInfo e) override;

    Vector3 GetStandardColor();
    Vector3 GetOnClickColor();
    Vector3 GetOnHoverColor();

};

