#pragma once
#include "Component.h"
#include "Graphics/Background.h"
#include "Graphics/SimpleBorder.h"
#include "Graphics/Text.h"
#include "GraphicalStates/DefaultButtonBehavior.h"

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
	 * \return returns the background color of the thumbTrack.
	 */
	Gdiplus::Color GetBackgroundColor();

	/*
	 * \return returns the border color of the thumbTrack.
	 */
	Gdiplus::Color GetBorderColor();


	/**
	 * \param color sets the color of the border.
	 */
	void SetBackgroundColor(Color color);

	/**
	 * \param thickness sets the border thickness of the thumbTrack.
	 */
	void SetBorderThickness(float thickness);
	void SetOnHoverColor(Gdiplus::Color color);
	void SetOnClickColor(Gdiplus::Color color);
	void SetColor(Gdiplus::Color color);
	Gdiplus::Color GetColor();

	Color GetOnClickColor();
	Color GetOnHoverColor();
	~Button();
};

