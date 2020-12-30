#pragma once
#include "Component.h"
/**
* Pane is a basic form of grouping. The purpose of Pane is having its own
* viewport and group multiple components together.
*/

class Pane : public Component
{
private:
	SolidBrush* brush;
public:
	virtual void Paint(Graphics& g) override;
	virtual void SetPosition(int x, int y) override;
	virtual void SetPosition(Point pos) override;
	virtual void UpdateComponent();
	void SetColor(int r, int g, int b);
	Pane();
	~Pane();
};

