#pragma once
#include "Component.h"
#include "Background.h"
#include "Text.h"

class Label : public Component
{
private:
	Background background;
	Text text;
public:
	Label(std::string name);
	Label();
	Label(int x, int y, int width, int height, std::string name);
	void SetBackground(Gdiplus::Color color);
	void GetBackground(Gdiplus::Color color);
	void SetText(std::wstring str);
	std::wstring GetText();
};

