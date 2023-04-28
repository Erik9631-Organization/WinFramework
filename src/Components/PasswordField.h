#pragma once
#include "UiElement.h"
#include "Text.h"
#include "TextInputBehavior.h"
#include "Text2.h"
#include "Border.h"

class PasswordField : public UiElement, public TextInputApi
{
private:
	Text2 text;
    std::wstring realText;
	Background background;
	Border border;
	TextInputBehavior behavior;
    float borderWidth = 1.0f;

public:
	PasswordField();

	/**
	 * \param x the X viewPortSize of the grid.
	 * \param y the Y viewPortSize of the grid
	 * \param width the width of the grid
	 * \param height the height of the grid.
	 * \param name the identification name of the grid. This is not a display value.
	 */
	PasswordField(int x, int y, int width, int height, std::string windowName);

	/**
	 * \param name the identification name of the grid. This is not a display value.
	 */
	explicit PasswordField(std::string name);

	
	void SetText(std::wstring text) override;

	/**
	 * \param color sets the background color.
	 */
	void SetBackgroundColor(const glm::vec4 &color);

    const std::wstring &GetText() override;

    const glm::ivec4 &GetBackgroundColor() override;

    void SetBackgroundColor(const glm::ivec4 &color) override;

    void SetPosition(const glm::vec4 &position, bool emit = true) override;

    void SetSize(const glm::vec4 &size, bool emit = true) override;
};

