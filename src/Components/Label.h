#pragma once
#include "UiElement.h"
#include "Graphics/Background.h"
#include "Graphics/Text.h"
#include "Text2.h"

/**
 * A component made for descriptive purposes. It displays text with a background.
 */
class Label : public UiElement
{
private:
	Background background;
	Text2 text;
public:
	/**
	 * \param name the identification name of the component. This value is not a display value.
	 */
	Label(const std::string &name);
	Label();

	/**
	 * \param x the X viewPortSize of the grid.
	 * \param y the Y viewPortSize of the grid
	 * \param width the width of the grid
	 * \param height the height of the grid.
	 * \param name the identification name of the grid. This is not a display value.
	 */
	Label(int x, int y, int width, int height, std::string name);

	/**
	 * \param color sets the color of the background.
	 */
	void SetBackground(const glm::vec4 &color);

	/**
	 * \return gets the color of the background.
	 */
    const glm::ivec4 & GetBackground();

	/**
	 * \param str sets the display value of the label.
	 */
	void SetText(std::wstring str) override;

	/**
	 * \return gets the display value of the label.
	 */
    const std::wstring & GetText() override;
};

