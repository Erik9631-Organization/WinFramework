#pragma once
#include <Windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
class Border
{
protected:
	Pen* pen;
	Size& size;
	Point& point;
	Color* color;
	SolidBrush* brush;
	float thickness;
public:
	void Paint(Graphics& g);
	void SetBorderThickness(float thickness);
	void SetBorderColor(COLORREF color);

	Border(Size& size, Point& point);
	~Border();
};

