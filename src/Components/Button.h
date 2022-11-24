#pragma once
#include "UiElement.h"
#include "Graphics/Background.h"
#include "Graphics/SimpleBorder.h"
#include "Graphics/Text.h"
#include "DefaultButtonBehavior.h"

class Button : public UiElement
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
	void SetBorderColor(Vector3 color);

	/**
	 * \param color sets the color of the background.
	 */
	void SetBackgroundColor(Vector3 color);


	/**
	 * \return returns the background color of the thumbTrack.
	 */
    Vector3 GetBackgroundColor();

	/*
	 * \return returns the border color of the thumbTrack.
	 */
    Vector3 GetBorderColor();


	/**
	 * \param thickness sets the border thickness of the thumbTrack.
	 */
	void SetBorderThickness(float thickness);
	void SetOnHoverColor(Vector3 color);
	void SetOnClickColor(Vector3 color);
	void SetColor(Vector3 color);
	Vector3 GetColor();

	Vector3 GetOnClickColor();
	Vector3 GetOnHoverColor();
	~Button();
};

