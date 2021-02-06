#pragma once
#include "RenderableSubscriber.h"
#include <vector>
class Renderable : public RenderableSubscriber
{
public:
	virtual void Repaint() = 0;
	virtual void AddRenderable(Renderable& renderable) = 0;
	virtual void RemoveRenderable(Renderable& renderable) = 0;
	virtual std::vector <std::reference_wrapper<Renderable>> GetRenderables() = 0;
};

