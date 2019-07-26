#include "Border.h"
#include "CoreWindowFrame.h"
void Border::Paint(Graphics & g)
{
	g.DrawRectangle(pen, point.X, point.Y, size.Width, size.Height);
}

void Border::SetBorderThickness(float thickness)
{
	pen->SetWidth(thickness);
}

void Border::SetBorderColor(COLORREF color)
{
	this->color->SetFromCOLORREF(color);
	pen->SetColor(*(this->color));
}

Border::Border(Size& size, Point& point) : size(size), point(point)
{
	color = new Color(0, 0, 0);
	brush = new SolidBrush(*color);
	pen = new Pen(brush, 1.0f);
}


Border::~Border()
{
	delete pen;
	delete brush;
}
