#pragma once
#include "Component.h"
#include "Background.h"
#include "SimpleBorder.h"
class Animation;
class Button : public Component
{

private:
	SimpleBorder border;
	Background background;
public:
	Button(int x, int y, int width, int height);
	void SetBorderColor(COLORREF color);
	void SetBackgroundColor(COLORREF color);
	void SetBorderThickness(float thickness);
	~Button();
};

