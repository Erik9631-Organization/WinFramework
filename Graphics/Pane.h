#pragma once
#include "Component.h"
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

