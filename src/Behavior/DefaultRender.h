#pragma once
#include "api/RenderCommander.h"
#include <vector>
#include <Renderer.h>
#include <mutex>

class DefaultRender : public RenderCommander
{
private:
	RenderCommander& assosiactedRenderable;
	std::vector<std::reference_wrapper<RenderCommander>> renderables;
    std::mutex addRenderableMutex;
public:
	// Inherited via Renderable
	DefaultRender(RenderCommander& renderable);

	virtual void OnRender(RenderEventInfo e) override;
	virtual void Repaint() override;
	virtual void AddRenderCommander(RenderCommander &renderable) override;
	virtual void RemoveRenderCommander(RenderCommander& renderable) override;
	virtual std::vector<std::reference_wrapper<RenderCommander>> GetRenderables() override;
    void OnSync(const DrawData& data) override;
};

