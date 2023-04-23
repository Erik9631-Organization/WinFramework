#pragma once
#include "Components/UiElement.h"
#include "Graphics/Text.h"
#include "Graphics/Background.h"
#include "TextInputBehavior.h"
#include "Graphics/SimpleBorder.h"
#include "Border.h"
#include "Text2.h"
#include "TextInputApi.h"

class TextInput : public UiElement, public TextInputApi
{
private:
	Background background;
	Border border;
	Text2 text;
	TextInputBehavior inputBehavior;
    float borderWidth = 1.0f;
public:
    const glm::ivec4& GetBackgroundColor() override;

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
	void SetBackgroundColor(const glm::ivec4 &color) override;

    const std::wstring &GetText() override;

    void SetPosition(glm::vec4 position) override;

    void SetSize(const glm::vec4 &size, bool emit) override;
};

