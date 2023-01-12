#pragma once
#include "Events/MouseStateSubscriber.h"

class Button;
class DefaultButtonBehavior : public MouseStateSubscriber
{
private:
	Button& associatedButton;
	glm::vec3 standardColor;
    glm::vec3 onClickColor;
    glm::vec3 onHoverColor;
public:
	DefaultButtonBehavior(Button& button);
	void SetOnHoverColor(glm::vec3 color);
	void SetOnClickColor(glm::vec3 color);
	void SetStatelessColor(glm::vec3 statelessColor);

	// Inherited via MouseStateSubscriber
	virtual void OnMouseDown(EventMouseStateInfo e) override;
	virtual void OnMouseUp(EventMouseStateInfo e) override;
	virtual void OnMousePressed(EventMouseStateInfo e) override;
	virtual void OnMouseMove(EventMouseStateInfo e) override;
	virtual void OnMouseEntered(EventMouseStateInfo e) override;
	virtual void OnMouseLeft(EventMouseStateInfo e) override;
    void OnMouseCaptured(EventMouseStateInfo e) override;

    glm::vec3 GetStandardColor();
    glm::vec3 GetOnClickColor();
    glm::vec3 GetOnHoverColor();

};

