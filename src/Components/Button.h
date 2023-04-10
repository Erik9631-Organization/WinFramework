#pragma once
#include "UiElement.h"
#include "Graphics/Background.h"
#include "Graphics/SimpleBorder.h"
#include "Graphics/Text.h"
#include "DefaultButtonBehavior.h"
#include "RectangleProxy.h"
#include "Border.h"
#include "Text2.h"

class Button : public UiElement
{

private:
    Border border;
    Background background;
	Text2 text;
	DefaultButtonBehavior buttonBehavior;
public:
    Button(float x, float y, float width, float height, const std::string &name);
	/**
	 * \param text unicode text of the thumbTrack which is to be displayed.
	 */
	void SetText(std::wstring text) override;

	/**
	 * \return returns the unicode text of the thumbTrack which is displayed.
	 */
	std::wstring GetText() override;

	/**
	 * \return returns the background color of the thumbTrack.
	 */
    const glm::ivec4 & GetBackgroundColor();

	/*
	 * \return returns the border color of the thumbTrack.
	 */
    const glm::ivec4 & GetBorderColor();


	/**
	 * \param thickness sets the border thickness of the thumbTrack.
	 */
	void SetBorderThickness(float thickness);
	void SetOnHoverColor(const glm::ivec4 &color);
	void SetOnClickColor(const glm::vec4 &color);

    /**
     * \param color sets the color of the background.
     */
    void SetBackgroundColor(const glm::ivec4 &color);

    void SetStatelessBackgroundColor(const glm::ivec4 &color);


    /**
     * \param color sets the color of the border.
     */
    void SetBorderColor(const glm::ivec4 &color);

	const glm::ivec4 & GetOnClickColor();
	const glm::ivec4 & GetOnHoverColor();
	~Button() override = default;
};

