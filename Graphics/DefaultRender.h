#pragma once
#include "Renderable.h"
#include <vector>

class DefaultRender : public Renderable
{
private:
	Renderable& assosiactedRenderable;
	std::vector<std::reference_wrapper<Renderable>> renderables;
public:
	// Inherited via Renderable
	DefaultRender(Renderable& renderable);

	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderable(Renderable& renderable) override;
	virtual void RemoveRenderable(Renderable& renderable) override;
	virtual std::vector<std::reference_wrapper<Renderable>> GetRenderables() override;
};

