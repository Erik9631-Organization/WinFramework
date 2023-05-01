#pragma once
#include "Events/MouseStateSubscriber.h"

class Button;
class DefaultButtonBehavior : public MouseStateSubscriber
{
private:
	Button& associatedButton;
	glm::ivec4 backgroundColor = {30, 30, 30, 255};
    glm::ivec4 onClickBackgroundColor = {60, 60, 60, 255};;
    glm::ivec4 onHoverBackgroundColor = {100, 100, 100, 255};
public:
	explicit DefaultButtonBehavior(Button& button);
	void SetOnHoverBackgroundColor(const glm::ivec4 &color);
	void SetOnClickBackgroundColor(const glm::ivec4 &color);
	void SetBackgroundColor(const glm::ivec4 &statelessColor);

    void OnMouseDown(EventMouseStateInfo e) override;
    void OnMouseUp(EventMouseStateInfo e) override;
    void OnMousePressed(EventMouseStateInfo e) override;
    void OnMouseMove(EventMouseStateInfo e) override;
    void OnMouseEntered(EventMouseStateInfo e) override;
    void OnMouseLeft(EventMouseStateInfo e) override;
    void OnMouseCaptured(EventMouseStateInfo e) override;

    const glm::ivec4 & GetStandardColor();
    const glm::ivec4 & GetOnClickColor();
    const glm::ivec4 & GetOnHoverColor();

};

