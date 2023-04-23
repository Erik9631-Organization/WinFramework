#pragma once
#include "Components/UiElement.h"
#include "Graphics/Text.h"
#include "TextInputBehavior.h"

class PasswordField : public UiElement, public TextInputApi
{
private:
	Text text;
    std::wstring realText;
	//Background background;
	SimpleBorder border;
	TextInputBehavior behavior;

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
	PasswordField(std::string name);

	
	void SetText(std::wstring text) override;

	/**
	 * \param color sets the background color.
	 */
	void SetBackgroundColor(glm::vec3 color);

    const std::wstring &GetText() override;

    const glm::ivec4 &GetBackgroundColor() override;

    void SetBackgroundColor(const glm::ivec4 &color) override;
};

