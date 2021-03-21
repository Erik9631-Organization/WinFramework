#pragma once
#include "Renderable.h"
#include "CircleBorder.h"
class CircleBackground : public CircleBorder
{
public:
	virtual void OnRender(RenderEventInfo e) override;
};

