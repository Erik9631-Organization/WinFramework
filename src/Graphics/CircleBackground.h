#pragma once
#include "api/RenderCommander.h"
#include "CircleBorder.h"
class CircleBackground : public CircleBorder
{
public:
	virtual void OnRenderSync(RenderEventInfo e) override;
};

