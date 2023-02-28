#pragma once
#include "UiElement.h"
#include "Graphics/Background.h"
#include "Graphics/SimpleBorder.h"
#include "Graphics/Text.h"
#include "DefaultButtonBehavior.h"
#include "RectangleProxy.h"
#include "Border.h"

class Button : public UiElement
{

private:
    Border border;
    Background background;
	Text text;
	DefaultButtonBehavior buttonBehavior;

public:
	Button(int x, int y, int width, int height);
	
	/**
	 * \param text unicode text of the thumbTrack which is to be displayed.
	 */
	void SetText(std::wstring text) override;

	/**
	 * \return returns the unicode text of the thumbTrack which is displayed.
	 */
	std::wstring GetText() override;

	/**
	 * \param color sets the color of the border.
	 */
	void SetBorderColor(glm::vec3 color);

	/**
	 * \param color sets the color of the background.
	 */
	void SetBackgroundColor(const glm::vec4 &color);


	/**
	 * \return returns the background color of the thumbTrack.
	 */
    glm::vec3 GetBackgroundColor();

	/*
	 * \return returns the border color of the thumbTrack.
	 */
    glm::vec3 GetBorderColor();


	/**
	 * \param thickness sets the border thickness of the thumbTrack.
	 */
	void SetBorderThickness(float thickness);
	void SetOnHoverColor(glm::vec3 color);
	void SetOnClickColor(glm::vec3 color);
	void SetColor(glm::vec3 color);
	glm::vec3 GetColor();

	glm::vec3 GetOnClickColor();
	glm::vec3 GetOnHoverColor();
	~Button();

    void OnMounted(Presenter &presenter, UiElement &element) override;
};

