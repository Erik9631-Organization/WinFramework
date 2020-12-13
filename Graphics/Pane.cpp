#include "Pane.h"
#include "WindowFrame.h"
#include "CoreWindowFrame.h"
#include "string"
void Pane::Paint(Graphics & g)
{
	CoreWindowFrame::ConsoleWrite("Works\n");
	g.FillRectangle(brush, pos.X, pos.Y, size.Width, size.Height);
}

void Pane::SetPosition(int x, int y)
{
	Component::SetPosition(x, y);

	if (parent == NULL)
		return;

	if (typeid(*parent) == typeid(WindowFrame))
	{
		pos.X = x;
		pos.Y = y;
		return;
	}
}

void Pane::SetPosition(Point pos)
{
	this->pos = pos;
}

void Pane::UpdateComponent()
{
	SetPosition(pos.X, pos.Y);
}

void Pane::SetColor(int r, int g, int b)
{
	brush->SetColor(Color(r, g ,b));
}

Pane::Pane() : Component()
{
	brush = new SolidBrush(Color(255, 0, 0));
}


Pane::~Pane()
{
}
