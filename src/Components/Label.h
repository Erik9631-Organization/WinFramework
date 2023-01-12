#pragma once
#include "UiElement.h"
#include "Graphics/Background.h"
#include "Graphics/Text.h"
/**
 * A component made for descriptive purposes. It displays text with a background.
 */
class Label : public UiElement
{
private:
	Background background;
	Text text;
public:
	/**
	 * \param name the identification name of the component. This value is not a display value.
	 */
	Label(std::string name);
	Label();

	/**
	 * \param x the X position of the grid.
	 * \param y the Y position of the grid
	 * \param width the width of the grid
	 * \param height the height of the grid.
	 * \param name the identification name of the grid. This is not a display value.
	 */
	Label(int x, int y, int width, int height, std::string name);

	/**
	 * \param color sets the color of the background.
	 */
	void SetBackground(glm::vec3 color);

	/**
	 * \return gets the color of the background.
	 */
    glm::vec3 GetBackground();

	/**
	 * \param str sets the display value of the label.
	 */
	void SetText(std::wstring str) override;

	/**
	 * \return gets the display value of the label.
	 */
	std::wstring GetText() override;
};

