#pragma once
#include "Components/UiElement.h"
#include "Graphics/Text.h"
#include "Graphics/Background.h"
#include "TextInputBehavior.h"
#include "Graphics/SimpleBorder.h"
class TextInput : public UiElement
{
private:
	// Background background;
	SimpleBorder border;
	Text text;
	TextInputBehavior inputBehavior;

public:
	TextInput();
	/**
	 * \param x the X viewPortSize of the grid.
	 * \param y the Y viewPortSize of the grid
	 * \param width the width of the grid
	 * \param height the height of the grid.
	 * \param name the identification name of the grid. This is not a display value.
	 */
	TextInput(int x, int y, int width, int height, std::string windowName);

	/**
	 * \param name the identification name of the grid. This is not a display value.
	 */
	TextInput(std::string name);


	void SetText(std::wstring text) override;
    std::wstring GetText() override;
	/**
	 * \return returns the background color.
	 */
    glm::vec3 GetBackgroundColor();

	/**
	 * \param state sets whether the text field is multiline.
	 */
	void SetMultiline(bool state);
	
	/**
	 * \return returns whether the textfield is multiline.
	 */
	bool IsMultiLine();

	/**
	 * \param color sets the background color.
	 */
	void SetBackgroundColor(glm::vec3 color);
};

