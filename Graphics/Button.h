#pragma once
#include "Component.h"
#include "Background.h"
#include "SimpleBorder.h"
#include "Text.h"
#include "ButtonGraphicalState.h"

class Animation;

/**
 * 
 */
class Button : public Component
{

private:
	SimpleBorder border;
	Background background;
	Text text;
	ButtonGraphicalState mouseGraphicalState;

public:
	Button(int x, int y, int width, int height);
	
	/**
	 * \param text unicode text of the button which is to be displayed.
	 */
	void SetText(std::wstring text) override;

	/**
	 * \return returns the unicode text of the button which is displayed.
	 */
	std::wstring GetText() override;

	/**
	 * \param color sets the color of the border.
	 */
	void SetBorderColor(COLORREF color);

	/**
	 * \param color sets the color of the background.
	 */
	void SetBackgroundColor(COLORREF color);

	/**
	 * \param color sets the color of the border.
	 */
	void SetBorderColor(Color color);


	/**
	 * \return returns the background color of the button.
	 */
	Gdiplus::Color GetBackgroundColor();

	/*
	 * \return returns the border color of the button.
	 */
	Gdiplus::Color GetBorderColor();


	/**
	 * \param color sets the color of the border.
	 */
	void SetBackgroundColor(Color color);

	/**
	 * \param thickness sets the border thickness of the button.
	 */
	void SetBorderThickness(float thickness);
	~Button();
};

