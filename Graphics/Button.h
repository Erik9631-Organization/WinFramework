#pragma once
#include "Component.h"
#include "Background.h"
#include "SimpleBorder.h"
#include "Text.h"
#include "ButtonGraphicalState.h"

class Animation;
class Button : public Component
{

private:
	SimpleBorder border;
	Background background;
	Text text;
	ButtonGraphicalState mouseGraphicalState;

public:
	Button(int x, int y, int width, int height);
	void SetText(std::wstring text);
	std::wstring GetText();
	void SetBorderColor(COLORREF color);
	void SetBackgroundColor(COLORREF color);
	void SetBorderColor(Color color);

	Gdiplus::Color GetBackgroundColor();
	Gdiplus::Color GetBorderColor(Color color);

	void SetBackgroundColor(Color color);
	void SetBorderThickness(float thickness);
	~Button();
};

