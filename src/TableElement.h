#pragma once
#include "Components/Label.h"
#include <any>
#include <Windows.h>
#include <gdiplus.h>

class TableElement : public Label
{
private:
	bool selected = false;
	std::any value;
	Gdiplus::Color highlightColor;
	Gdiplus::Color originalcolor;
public:
	TableElement();
	TableElement(std::string name);
	TableElement(int x, int y, int width, int height, std::string name);

	void SetValue(std::any value);
	std::any GetValue();
	bool IsSelected();
	void SetSelected(bool selected);

};

